#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{

    int pid = fork();

    if (pid == 0) // child block
    {
        while (1)
        {
            printf("stuck in child\n");
        }
    }
    else
    {
        sleep(2);
        // kill(pid, SIGKILL);
        kill(pid, SIGSEGV);
    }
    wait(NULL);
    return 0;
}