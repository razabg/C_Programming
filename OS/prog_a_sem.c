#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>

int main()
{
    // Create the semaphore if it doesn't exist yet, initialized to 1
    // (binary semaphore — acts as a mutex for the log file)
    sem_t *log_sem = sem_open("/log-file-sem", O_CREAT, 0644, 1);
    if (log_sem == SEM_FAILED)
    {
        perror("sem_open failed");
        return 1;
    }

    // --- Wait for exclusive access ---
    sem_wait(log_sem); // down: blocks if another process holds it

    FILE *f = fopen("shared.log", "a");
    fprintf(f, "Program A writing an entry\n");
    fclose(f);

    // --- Release access ---
    sem_post(log_sem); // up: lets a waiting process proceed

    sem_close(log_sem); // done with this process's handle
    // NOTE: does NOT call sem_unlink here — see explanation below
    return 0;
}