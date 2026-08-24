#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ohh(int sig)
{
    printf("Ohh! I got signal %d\n", sig);
    fflush(stdout);
    signal(SIGINT, SIG_DFL); /* the NEXT SIGINT reverts to killing the process */
}

int main(void)
{
    signal(SIGINT, ohh);
    while (1)
    {
        printf("Hello World!\n");
        fflush(stdout);
        sleep(1);
    }
    return 0;
}