#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>

int main()
{
    // Opens the SAME named semaphore (already created by A, or creates it
    // if B happens to run first — O_CREAT handles both orders safely)
    sem_t *log_sem = sem_open("/log-file-sem", O_CREAT, 0644, 1);
    if (log_sem == SEM_FAILED)
    {
        perror("sem_open failed");
        return 1;
    }

    sem_wait(log_sem); // down: waits its turn if A currently holds it

    FILE *f = fopen("shared.log", "a");
    fprintf(f, "Program B writing an entry\n");
    fclose(f);

    sem_post(log_sem); // up: releases the lock

    sem_close(log_sem);
    return 0;
}