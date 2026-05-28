#include <sys/socket.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

#define BACKLOG 10

/*
 * === DOUBLY LINKED LIST IMPROVEMENT ===
 *
 * PROBLEM with current approach:
 *   - The loop `for (int i = 0; i <= max_fd; i++)` iterates over EVERY fd
 *     from 0 to max_fd, even empty slots. With 5 clients and max_fd=47,
 *     you check 48 slots unnecessarily.
 *   - max_fd never shrinks when the highest-fd client disconnects.
 *
 * SOLUTION: keep a doubly linked list of active client nodes.
 *   - Iterate only real clients → O(n_clients) instead of O(max_fd).
 *   - O(1) removal (with a pointer to the node).
 *   - Recalculate max_fd by scanning the list only after a disconnect.
 *   - Each node can carry extra per-client data (addr, partial read buffer, etc).
 *
 * SUGGESTED DATA STRUCTURES:
 *
 *   typedef struct ClientNode {
 *       int fd;
 *       struct ClientNode *prev;
 *       struct ClientNode *next;
 *   } ClientNode;
 *
 *   typedef struct { ClientNode *head; } ClientList;
 *
 * SUGGESTED HELPERS:
 *
 *   ClientNode *client_add(ClientList *list, int fd) {
 *       ClientNode *node = malloc(sizeof(ClientNode));
 *       node->fd = fd;
 *       node->prev = NULL;
 *       node->next = list->head;
 *       if (list->head) list->head->prev = node;
 *       list->head = node;
 *       return node;          // store this pointer to enable O(1) removal
 *   }
 *
 *   void client_remove(ClientList *list, ClientNode *node) {
 *       if (node->prev) node->prev->next = node->next;
 *       else            list->head        = node->next;
 *       if (node->next) node->next->prev  = node->prev;
 *       free(node);
 *   }
 *
 *   int max_fd_from_list(const ClientList *list, int server_fd) {
 *       int max = server_fd;
 *       for (ClientNode *n = list->head; n; n = n->next)
 *           if (n->fd > max) max = n->fd;
 *       return max;           // called only after a disconnect, not every loop
 *   }
 *
 * USAGE IN MAIN LOOP:
 *
 *   // On accept:
 *   client_add(&clients, client_fd);
 *
 *   // Replace  for (int i = 0; i <= max_fd; i++) { FD_ISSET(i, ...) }  with:
 *   for (ClientNode *node = clients.head; node; ) {
 *       ClientNode *next = node->next;          // save before possible free
 *       if (FD_ISSET(node->fd, &readfds)) {
 *           ... handle data / disconnect ...
 *           if (disconnected) {
 *               client_remove(&clients, node);
 *               max_fd = max_fd_from_list(&clients, sock);   // shrinks max_fd
 *           }
 *       }
 *       node = next;
 *   }
 */

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

        // INEFFICIENCY: iterates 0..max_fd, most slots are empty
        // With DLL: replace this with  for (ClientNode *n = clients.head; n; )
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

                    // With DLL: also call  client_add(&clients, client_fd);
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
                        // With DLL: client_remove(&clients, node);
                        //           max_fd = max_fd_from_list(&clients, sock);
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
