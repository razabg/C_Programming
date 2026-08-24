#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    printf("about to signal myself with SIGABRT (pid=%d)\n", getpid());
    fflush(stdout);
    if (kill(getpid(), SIGABRT))
    {
        perror("kill failed");
        exit(1);
    }
    printf("this line never runs -- SIGABRT's default action is to terminate\n");
    return 0;
}