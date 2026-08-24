#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

void counter(int sig)
{
    (void)sig;            /* silence unused-parameter warning */
    static int count = 0; /* renamed to avoid shadowing the function name, and typed */
    count++;
    if (count == 2)
    {
        signal(SIGINT, SIG_DFL);
        printf("control + C clicked twice! next time the program will die!\n");
        fflush(stdout);
    }
}

int main(void)
{
    signal(SIGINT, counter);
    while (true)
    {
        printf("hello!\n");
        fflush(stdout);
        sleep(1);
    }
    return 0;
}