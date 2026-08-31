/*
 * =====================================================================
 * mutex_demo.c
 * =====================================================================
 *
 * PURPOSE:
 *   Demonstrates the use of a POSIX pthread MUTEX to synchronize two
 *   threads accessing a shared resource.
 *
 * WHY A MUTEX (vs. the binary semaphore in unamed_sem.c):
 *   - A mutex is OWNED by the thread that locks it: only that same
 *     thread may unlock it. A binary semaphore has no owner -- any
 *     thread can post() it, even one that never called wait().
 *   - Mutexes are the natural fit when the goal is simple mutual
 *     exclusion around a critical section (exactly this case).
 *     Semaphores are more general -- they also work for signaling
 *     between threads and for counting multiple available resources.
 *
 * WHAT THIS PROGRAM DOES:
 *   Two threads each increment a shared counter 5 times. The mutex
 *   guarantees mutual exclusion around the shared counter's critical
 *   section, preventing a race condition.
 *
 * COMPILE:
 *   gcc -o mutex_demo mutex_demo.c -lpthread
 *
 * RUN:
 *   ./mutex_demo
 *
 * EXPECTED OUTPUT:
 *   10 lines, each showing the counter incrementing by exactly 1,
 *   with NO duplicate or skipped values -- proof mutual exclusion works.
 * =====================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> /* for usleep() -- used to widen the race window */

/* ---------------------------------------------------------------------
 * Shared state
 * --------------------------------------------------------------------- */
static pthread_mutex_t counter_mutex; /* guards shared_counter */
static int shared_counter = 0;
static const int ITERATIONS_PER_THREAD = 5;

/* ---------------------------------------------------------------------
 * thread_worker()
 *
 * Each thread runs this function. Every iteration:
 *   1. pthread_mutex_lock()   -> enter critical section (blocks if busy)
 *   2. modify the shared counter
 *   3. pthread_mutex_unlock() -> leave critical section, wake any waiter
 *
 * The usleep() call INSIDE the critical section is intentional: it
 * artificially widens the window where a race condition WOULD occur
 * if the mutex were missing, making the protection easy to verify.
 * --------------------------------------------------------------------- */
void *thread_worker(void *arg)
{
    const char *thread_name = (const char *)arg;

    for (int i = 0; i < ITERATIONS_PER_THREAD; i++)
    {
        pthread_mutex_lock(&counter_mutex); /* ---- enter critical section ---- */

        int local_copy = shared_counter; /* read */
        usleep(10000);                   /* simulate work (widens race window) */
        local_copy++;                    /* modify */
        shared_counter = local_copy;     /* write back */

        printf("[%s] incremented counter to %d\n", thread_name, shared_counter);

        pthread_mutex_unlock(&counter_mutex); /* ---- leave critical section ---- */
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
     * pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
     *
     *   attr = NULL -> default attributes: fast (non-recursive), usable
     *                  only by threads of THIS process (no PTHREAD_PROCESS_SHARED).
     *                  A mutex always starts "unlocked" -- there is no
     *                  initial-value argument like sem_init() has.
     */
    if (pthread_mutex_init(&counter_mutex, NULL) != 0)
    {
        perror("pthread_mutex_init failed");
        return EXIT_FAILURE;
    }

    /* Launch both threads; each increments shared_counter 5 times */
    if (pthread_create(&thread_a, NULL, thread_worker, (void *)"Thread-A") != 0)
    {
        perror("pthread_create (A) failed");
        pthread_mutex_destroy(&counter_mutex);
        return EXIT_FAILURE;
    }

    if (pthread_create(&thread_b, NULL, thread_worker, (void *)"Thread-B") != 0)
    {
        perror("pthread_create (B) failed");
        pthread_mutex_destroy(&counter_mutex);
        return EXIT_FAILURE;
    }

    /* Wait for both threads to finish before checking the final result */
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);

    printf("\nFinal counter value: %d (expected: %d)\n",
           shared_counter, ITERATIONS_PER_THREAD * 2);

    /* Clean up: destroy the mutex now that no thread needs it */
    pthread_mutex_destroy(&counter_mutex);

    return EXIT_SUCCESS;
}
