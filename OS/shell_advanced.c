#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   // fork, execvp, chdir, getcwd
#include <sys/wait.h> // waitpid
#include <fcntl.h>    // open, O_WRONLY, O_RDONLY
#include <signal.h>   // signal, SIGINT

#define BUFFER_SIZE 1024
#define MAX_ARGS 64
#define MAX_PATH 1024

// ─────────────────────────────────────────────────────────────
// PROMPT
// getcwd() fills cwd with the absolute path of the current dir.
// fflush(stdout) forces the prompt to appear before fgets blocks.
// ─────────────────────────────────────────────────────────────
void show_prompt()
{
    char cwd[MAX_PATH];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        printf("$ ");
    }
    else
    {
        printf("razabg@shell:%s$ ", cwd);
    }
    fflush(stdout);
}

// ─────────────────────────────────────────────────────────────
// TOKENIZER
// Splits the raw input string into an array of word pointers.
// strtok modifies the input buffer in place and returns pointers
// into it, so args[] must not outlive the buffer.
// ─────────────────────────────────────────────────────────────
int tokenize(char *input, char **args)
{
    int count = 0;
    char *token = strtok(input, " \t\r\n\a");
    while (token != NULL && count < MAX_ARGS - 1)
    {
        args[count++] = token;
        token = strtok(NULL, " \t\r\n\a");
    }
    args[count] = NULL; // execvp requires NULL-terminated array
    return count;
}

// ─────────────────────────────────────────────────────────────
// OUTPUT REDIRECTION  (cmd > file)
// Scans args for ">", opens the file for writing (creating it
// if it doesn't exist, truncating if it does), then removes
// both ">" and the filename from the args array so execvp
// never sees them. Returns the fd, or -1 if no ">" found.
// ─────────────────────────────────────────────────────────────
int handle_output_redirect(char **args, int *argc)
{
    for (int i = 0; i < *argc; i++)
    {
        if (strcmp(args[i], ">") == 0)
        {
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, "shell: syntax error near '>'\n");
                return -1;
            }
            int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
                perror("open");

            // Shift remaining args left by 2 to erase ">" and filename
            for (int j = i; j < *argc - 1; j++)
                args[j] = args[j + 2];
            *argc -= 2;
            args[*argc] = NULL;
            return fd;
        }
    }
    return -1;
}

// ─────────────────────────────────────────────────────────────
// INPUT REDIRECTION  (cmd < file)
// Same idea as output redirection, but opens for reading.
// ─────────────────────────────────────────────────────────────
int handle_input_redirect(char **args, int *argc)
{
    for (int i = 0; i < *argc; i++)
    {
        if (strcmp(args[i], "<") == 0)
        {
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, "shell: syntax error near '<'\n");
                return -1;
            }
            int fd = open(args[i + 1], O_RDONLY);
            if (fd == -1)
                perror("open");

            for (int j = i; j < *argc - 1; j++)
                args[j] = args[j + 2];
            *argc -= 2;
            args[*argc] = NULL;
            return fd;
        }
    }
    return -1;
}

// ─────────────────────────────────────────────────────────────
// EXECUTE SIMPLE COMMAND  (with optional redirection/background)
//
// dup2(fd, STDOUT_FILENO) makes file descriptor STDOUT_FILENO
// (which is 1) point to the same file as fd. After that, any
// write to stdout goes to the file instead of the terminal.
// We close the original fd afterwards because we no longer need
// two file descriptors pointing to the same file.
//
// background=1: parent does NOT waitpid, so the shell returns
// to the prompt immediately while the child runs in the background.
// ─────────────────────────────────────────────────────────────
void execute_simple(char **args, int argc, int background)
{
    int out_fd = handle_output_redirect(args, &argc);
    int in_fd = handle_input_redirect(args, &argc);

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0) // ── child ──
    {
        // Restore default Ctrl+C behaviour (parent ignores it, child must not)
        signal(SIGINT, SIG_DFL);

        if (out_fd != -1)
        {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
        if (in_fd != -1)
        {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }

        execvp(args[0], args);
        perror("exec");
        exit(1);
    }
    else // ── parent ──
    {
        if (out_fd != -1)
            close(out_fd);
        if (in_fd != -1)
            close(in_fd);

        if (!background)
            waitpid(pid, NULL, 0); // block until child is done
        else
            printf("[background] pid %d\n", pid); // don't wait — show pid
    }
}

// ─────────────────────────────────────────────────────────────
// EXECUTE PIPE  (left | right)
//
// pipe(pipefd) creates two connected file descriptors:
//   pipefd[0] = read  end
//   pipefd[1] = write end
//
// Child 1 (left side):  stdout → pipefd[1]  (writes into the pipe)
// Child 2 (right side): stdin  ← pipefd[0]  (reads from the pipe)
//
// The parent must close BOTH ends after forking, otherwise the
// right-side child will never see EOF on its stdin and will hang.
// ─────────────────────────────────────────────────────────────
void execute_pipe(char **left, int left_argc, char **right, int right_argc)
{
    (void)left_argc;
    (void)right_argc;

    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }

    // ── left child: writes to pipe ──
    pid_t pid1 = fork();
    if (pid1 < 0)
    {
        perror("fork");
        return;
    }
    if (pid1 == 0)
    {
        signal(SIGINT, SIG_DFL);
        dup2(pipefd[1], STDOUT_FILENO); // stdout → write end
        close(pipefd[0]);
        close(pipefd[1]);
        execvp(left[0], left);
        perror("exec");
        exit(1);
    }

    // ── right child: reads from pipe ──
    pid_t pid2 = fork();
    if (pid2 < 0)
    {
        perror("fork");
        return;
    }
    if (pid2 == 0)
    {
        signal(SIGINT, SIG_DFL);
        dup2(pipefd[0], STDIN_FILENO); // stdin ← read end
        close(pipefd[0]);
        close(pipefd[1]);
        execvp(right[0], right);
        perror("exec");
        exit(1);
    }

    // ── parent: close both ends, then wait for both children ──
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

// ─────────────────────────────────────────────────────────────
// MAIN LOOP
// ─────────────────────────────────────────────────────────────
int main()
{
    char input[BUFFER_SIZE];
    char *args[MAX_ARGS];

    // The shell itself ignores Ctrl+C.
    // Each child restores SIG_DFL before exec, so Ctrl+C kills
    // the running command but not the shell.
    signal(SIGINT, SIG_IGN);

    while (1)
    {
        show_prompt();

        // fgets returns NULL on EOF (Ctrl+D) — exit gracefully
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\nexit\n");
            break;
        }

        int argc = tokenize(input, args);
        if (argc == 0)
            continue; // user pressed Enter on an empty line

        // ── background check: trailing & ──
        // We strip "&" before any other processing.
        int background = 0;
        if (argc > 0 && strcmp(args[argc - 1], "&") == 0)
        {
            background = 1;
            args[--argc] = NULL;
        }

        // ── built-in: exit ──
        // execvp cannot run shell builtins — we must handle them ourselves.
        if (strcmp(args[0], "exit") == 0)
        {
            printf("Bye!\n");
            exit(0);
        }

        // ── built-in: cd ──
        // cd must run in the parent process. If we forked a child to
        // run chdir(), the parent's directory would never change.
        if (strcmp(args[0], "cd") == 0)
        {
            const char *dir = args[1] ? args[1] : getenv("HOME");
            if (chdir(dir) != 0)
                perror("cd");
            continue;
        }

        // ── pipe detection ──
        // Find the first "|" token and split args around it.
        int pipe_index = -1;
        for (int i = 0; i < argc; i++)
        {
            if (strcmp(args[i], "|") == 0)
            {
                pipe_index = i;
                break;
            }
        }

        if (pipe_index != -1)
        {
            char *left[MAX_ARGS];
            char *right[MAX_ARGS];

            int left_argc = pipe_index;
            int right_argc = argc - pipe_index - 1;

            for (int i = 0; i < left_argc; i++)
                left[i] = args[i];
            for (int i = 0; i < right_argc; i++)
                right[i] = args[pipe_index + 1 + i];
            left[left_argc] = NULL;
            right[right_argc] = NULL;

            execute_pipe(left, left_argc, right, right_argc);
        }
        else
        {
            execute_simple(args, argc, background);
        }
    }

    return 0;
}
