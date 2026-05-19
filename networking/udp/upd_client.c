#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main()
{

    struct sockaddr_in sin;


    char *message = "hello ezra";
    size_t message_len = strlen(message);

    u_int32_t sent_bytes;

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("192.168.1.78");
    sin.sin_port = htons(2008);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0)
    {
        perror("socket failed");

        abort();
    }

    sent_bytes = sendto(sock, message, message_len, 0,

                        (struct sockaddr *)&sin, sizeof(sin));

    if (sent_bytes < 0)
    {

        perror("sendto failed");

        abort();
    }

    close(sock);
    return 0;
}