#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Custom handler for SIGINT
void handler(int num)
{
    // write() is async-signal-safe, unlike printf()
    write(STDOUT_FILENO, "\nI won't die!\n", 15);
}

int main()
{
    // Register the custom handler for SIGINT
    signal(SIGINT, handler);

    while (1)
    {
        printf("Wasting your cycles. PID: %d\n", getpid());
        sleep(1);
    }

    return 0;
}

// the modern version
//  #include <stdio.h>
//  #include <stdlib.h>
//  #include <unistd.h>
//  #include <signal.h>

// // Async-signal-safe handler function
// void handler(int num) {
//     write(STDOUT_FILENO, "\nI won't die!\n", 15);
// }

// int main() {
//     struct sigaction sa;

//     // 1. Assign the custom handler function
//     sa.sa_handler = handler;

//     // 2. Initialize the signal mask to block no additional signals during execution
//     sigemptyset(&sa.sa_mask);

//     // 3. Set optional flags (0 for standard default behavior)
//     sa.sa_flags = 0;

//     // 4. Register the action for SIGINT (Ctrl+C)
//     sigaction(SIGINT, &sa, NULL);

//     while (1) {
//         printf("Wasting your cycles. %d\n", getpid());
//         sleep(1);
//     }

//     return 0;
// }