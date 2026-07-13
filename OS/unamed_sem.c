/*
 * =====================================================================
 * unnamed_semaphore_demo.c
 * =====================================================================
 *
 * PURPOSE:
 *   Demonstrates the use of an UNNAMED (memory-based) POSIX semaphore
 *   to synchronize two threads accessing a shared resource.
 *
 * WHY UNNAMED (not sem_open):
 *   - Both threads belong to the SAME process, so they already share
 *     the full address space (stack, heap, globals).
 *   - No filesystem name is needed (contrast with sem_open("/name",...)
 *     which is required for UNRELATED processes).
 *   - sem_init()/sem_destroy() manage the semaphore's lifetime directly
 *     in memory -- faster, no filesystem overhead.
 *
 * WHAT THIS PROGRAM DOES:
 *   Two threads each increment a shared counter 5 times. The semaphore
 *   is used as a BINARY semaphore (mutex-style, initialized to 1) to
 *   guarantee mutual exclusion around the shared counter's critical
 *   section, preventing a race condition.
 *
 * COMPILE:
 *   gcc -o sem_demo unnamed_semaphore_demo.c -lpthread
 *
 * RUN:
 *   ./sem_demo
 *
 * EXPECTED OUTPUT:
 *   10 lines, each showing the counter incrementing by exactly 1,
 *   with NO duplicate or skipped values -- proof mutual exclusion works.
 * =====================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> /* for usleep() -- used to widen the race window */

/* ---------------------------------------------------------------------
 * Shared state
 * --------------------------------------------------------------------- */
static sem_t mutex_sem; /* Binary semaphore: guards shared_counter */
static int shared_counter = 0;
static const int ITERATIONS_PER_THREAD = 5;

/* ---------------------------------------------------------------------
 * thread_worker()
 *
 * Each thread runs this function. Every iteration:
 *   1. sem_wait()  -> "down" -> enter critical section (blocks if busy)
 *   2. modify the shared counter
 *   3. sem_post()  -> "up"   -> leave critical section, wake any waiter
 *
 * The usleep() call INSIDE the critical section is intentional: it
 * artificially widens the window where a race condition WOULD occur
 * if the semaphore were missing, making the protection easy to verify.
 * --------------------------------------------------------------------- */
void *thread_worker(void *arg)
{
    const char *thread_name = (const char *)arg;

    for (int i = 0; i < ITERATIONS_PER_THREAD; i++)
    {

        sem_wait(&mutex_sem); /* ---- enter critical section ---- */

        int local_copy = shared_counter; /* read */
        usleep(10000);                   /* simulate work (widens race window) */
        local_copy++;                    /* modify */
        shared_counter = local_copy;     /* write back */

        printf("[%s] incremented counter to %d\n", thread_name, shared_counter);

        sem_post(&mutex_sem); /* ---- leave critical section ---- */
    }

    return NULL;
}

/* ---------------------------------------------------------------------
 * main()
 * --------------------------------------------------------------------- */
int main(void)
{
    pthread_t thread_a, thread_b;

    /*
     * sem_init(sem_t *sem, int pshared, unsigned int value)
     *
     *   pshared = 0  -> semaphore is shared between THREADS of this
     *                   process only (NOT across process boundaries).
     *                   Use pshared != 0 only if the semaphore lives in
     *                   memory shared via mmap(MAP_SHARED) BEFORE a fork().
     *
     *   value   = 1  -> binary semaphore, starts "unlocked" (1 permit
     *                   available), matching mutex-style mutual exclusion.
     */
    if (sem_init(&mutex_sem, 0, 1) != 0)
    {
        perror("sem_init failed");
        return EXIT_FAILURE;
    }

    /* Launch both threads; each increments shared_counter 5 times */
    if (pthread_create(&thread_a, NULL, thread_worker, (void *)"Thread-A") != 0)
    {
        perror("pthread_create (A) failed");
        sem_destroy(&mutex_sem);
        return EXIT_FAILURE;
    }

    if (pthread_create(&thread_b, NULL, thread_worker, (void *)"Thread-B") != 0)
    {
        perror("pthread_create (B) failed");
        sem_destroy(&mutex_sem);
        return EXIT_FAILURE;
    }

    /* Wait for both threads to finish before checking the final result */
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);

    printf("\nFinal counter value: %d (expected: %d)\n",
           shared_counter, ITERATIONS_PER_THREAD * 2);

    /* Clean up: destroy the semaphore now that no thread needs it */
    sem_destroy(&mutex_sem);

    return EXIT_SUCCESS;
}