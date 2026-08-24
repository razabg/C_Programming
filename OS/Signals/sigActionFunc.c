#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void ohh(int sig)
{
    printf("Ohh! I got signal %d\n", sig);
    fflush(stdout);
}

int main(void)
{
    struct sigaction act;
    act.sa_handler = ohh;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);

    while (1)
    {
        printf("Hello World!\n");
        fflush(stdout);
        sleep(1);
    }
}