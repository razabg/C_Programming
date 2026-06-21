#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   //  fork()
#include <sys/wait.h> //  waitpid()

#define BUFFER_SIZE 256

int main()
{

    char *list_of_strings[20];
    char prompt[BUFFER_SIZE];
    int counter = 0;
    char *token = NULL;
    const char *delimiters = " \t\r\n\a";
    __pid_t pid;

    while (1)
    {
        counter = 0; // reset the counter in order that execvp will now how many items in the list
        printf("razabg@razabg:~$");

        // 1. Safely read input
        if (fgets(prompt, sizeof(prompt), stdin) != NULL)
        {
        }

        token = strtok(prompt, delimiters);

        while (token != NULL)
        {
            list_of_strings[counter++] = token;
            token = strtok(NULL, delimiters);
        }

        list_of_strings[counter] = NULL; // because the execvp doesnt know where the list of strings end.

        if ((strcmp(list_of_strings[0], "exit")) == 0)
        {
            break;
        }

        pid = fork();

        if (pid == 0) // child section
        {
            execvp(list_of_strings[0], list_of_strings);
            perror("Exec failed!");
            exit(1);
        }
        else // parent section
        {
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}
