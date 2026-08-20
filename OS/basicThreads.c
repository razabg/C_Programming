#include <pthread.h>
#include <stdio.h>

// This example demonstrates that local variables are private to each thread (stored on its own stack),
// while global variables are shared across all threads and subject to race conditions without synchronization.

#define NUM_THREADS 10

int global = 0;

void *PrintFunc(void *param)
{
    int local = (int)(long)param; // private copy per thread

    printf("local  = %d  (thread %d's own stack)\n", local++, local);
    printf("global = %d  (shared!)\n", global++); // intentional race

    return NULL;
}

int main(void)
{
    pthread_t threadList[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        // pthread_create(thread, attr, start_routine, arg):
        //   thread        -> pthread_t out-param, filled with the new thread's ID
        //   attr          -> NULL = default attributes (stack size, scheduling, etc.)
        //   start_routine -> function the new thread runs: void *(*)(void *)
        //   arg           -> single value passed to start_routine (here, the loop index)
        int status = pthread_create(&threadList[i], NULL, PrintFunc, (void *)(long)i);
        if (status != 0)
            fprintf(stderr, "pthread_create failed: %d\n", status);
    }

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threadList[i], NULL);

    return 0;
}