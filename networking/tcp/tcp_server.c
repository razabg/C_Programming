#include <sys/socket.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

#define BACKLOG 10 //******************** add doubly linked list */

int main()
{

    struct sockaddr_in sin;

    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(8080);
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
    {
        perror("socket() failed");
        abort();
        return 0;
    }

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("bind failed");
        abort();
    }

    if (listen(sock, BACKLOG) < 0)
    {
        perror("listen failed");
        abort();
    }

    fd_set master_set;
    int max_fd = sock;
    FD_ZERO(&master_set);
    FD_SET(sock, &master_set);

    while (1)
    {
        fd_set readfds = master_set;
        int activity = select(max_fd + 1, &readfds, NULL, NULL, NULL);
        if (activity < 0)
        {
            perror("select failed");
            abort();
        }

        for (int i = 0; i <= max_fd; i++)
        {
            if (FD_ISSET(i, &readfds))
            {
                if (i == sock)
                {
                    struct sockaddr_in client_addr;
                    socklen_t client_len = sizeof(client_addr);

                    int client_fd = accept(sock, (struct sockaddr *)&client_addr, &client_len);
                    if (client_fd < 0)
                    {
                        perror("accept failed");
                        abort();
                    }

                    FD_SET(client_fd, &master_set);
                    if (client_fd > max_fd)
                        max_fd = client_fd;

                    printf("New client connected, fd = %d\n", client_fd);
                    fflush(stdout);
                }
                else
                {
                    char buffer[1024];
                    int bytes = read(i, buffer, sizeof(buffer));

                    if (bytes <= 0)
                    {
                        printf("Client fd %d disconnected\n", i);
                        fflush(stdout);
                        FD_CLR(i, &master_set);
                        close(i);
                    }
                    else
                    {
                        write(i, buffer, bytes);
                    }
                }
            }
        }
    }

    return 0;
}