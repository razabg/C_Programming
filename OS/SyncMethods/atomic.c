/*
 * =====================================================================
 * atomic_demo.c
 * =====================================================================
 *
 * PURPOSE:
 *   Demonstrates the C11 _Atomic keyword by comparing a PROTECTED
 *   atomic counter against an UNPROTECTED plain counter, both
 *   incremented concurrently by many threads.
 *
 * WHY THE ARTIFICIAL DELAY:
 *   count++ compiles to three separate steps:
 *       1) load count from memory into a register
 *       2) increment the register
 *       3) store the register back to memory
 *   On a fast, single-core machine, these three steps often complete
 *   before the OS scheduler switches threads, so the race condition
 *   may not show up "by luck" -- NOT because it isn't real, but
 *   because the unsafe window is too narrow to hit reliably.
 *
 *   To make the race condition reliably VISIBLE (even on a single
 *   core, or a fast multi-core box), we manually widen that window:
 *   we do the load/increment/store as separate C statements with a
 *   tiny sleep in between, simulating what the CPU does internally.
 *   This is purely a teaching aid -- real code would never do this.
 *
 * COMPILE:
 *   gcc -O0 -o atomic_demo atomic_demo.c -lpthread
 *   (Use -O0 so the compiler doesn't optimize/reorder our
 *    deliberately-separated load/inc/store steps.)
 *
 * RUN:
 *   ./atomic_demo
 *
 * EXPECTED RESULT:
 *   - atomic_count  -> ALWAYS exactly (NUM_THREADS * ITERATIONS)
 *   - unsafe_count  -> USUALLY less than expected -- lost updates
 * =====================================================================
 */

#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>

#define NUM_THREADS 10
#define ITERATIONS 1000

/* ---------------------------------------------------------------------
 * The two counters under test
 * --------------------------------------------------------------------- */
_Atomic int atomic_count = 0; /* protected: indivisible increment    */
int unsafe_count = 0;         /* unprotected: classic race condition */

/* ---------------------------------------------------------------------
 * atomic_worker()
 *
 * atomic_count++ compiles down to a single hardware-guaranteed atomic
 * instruction (e.g. LOCK XADD on x86). No other thread can observe or
 * interleave with it halfway through -- it either hasn't happened yet,
 * or it's fully done. No locks, no OS involvement, no busy-waiting.
 * --------------------------------------------------------------------- */
void *atomic_worker(void *arg)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        atomic_count++; /* single atomic instruction */
    }
    return NULL;
}

/* ---------------------------------------------------------------------
 * unsafe_worker()
 *
 * We manually spell out the three steps of "unsafe_count++" and
 * insert a tiny delay between them. This simulates what can happen
 * on real hardware: a context switch (or another core writing at the
 * same instant) landing exactly between load and store, causing one
 * thread's increment to be silently lost.
 * --------------------------------------------------------------------- */
void *unsafe_worker(void *arg)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        int temp = unsafe_count; /* step 1: load  */
        usleep(1);               /* widen the race window */
        temp = temp + 1;         /* step 2: increment (in a register) */
        unsafe_count = temp;     /* step 3: store */
    }
    return NULL;
}

/* ---------------------------------------------------------------------
 * main()
 * --------------------------------------------------------------------- */
int main(void)
{
    pthread_t atomic_threads[NUM_THREADS];
    pthread_t unsafe_threads[NUM_THREADS];

    int expected = NUM_THREADS * ITERATIONS;

    printf("Launching %d threads, %d increments each.\n", NUM_THREADS, ITERATIONS);
    printf("Expected final value for both counters: %d\n\n", expected);

    /* Launch all atomic-counter threads */
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&atomic_threads[i], NULL, atomic_worker, NULL);

    /* Launch all unsafe-counter threads */
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&unsafe_threads[i], NULL, unsafe_worker, NULL);

    /* Wait for everyone to finish */
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(atomic_threads[i], NULL);
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(unsafe_threads[i], NULL);

    printf("atomic_count (protected)   = %d  %s\n",
           atomic_count, (atomic_count == expected) ? "(correct)" : "(WRONG!)");
    printf("unsafe_count (unprotected) = %d  %s\n",
           unsafe_count, (unsafe_count == expected) ? "(correct -- got lucky)" : "(WRONG -- lost updates!)");

    return 0;
}