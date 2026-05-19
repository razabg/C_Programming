#include <sys/socket.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef int SOCKET;

int main(){
    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));

    SOCKET sock;

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("192.168.1.78");
    sin.sin_port = htons(2008);

    sock = socket(sin.sin_family,SOCK_DGRAM,0);

    if(sock < 0){
        perror("Socket failed");
        abort();

    }

    if(bind(sock,(struct sockaddr *) &sin, sizeof(sin)) > 0) {
        perror("bind fail");
        abort();

    }

    while(1){
        uint32_t sin_len;
        char buffer[4096];

        uint32_t read_bytes = recvfrom(sock, buffer, sizeof(buffer),
         0, (struct sockaddr* )&sin,&sin_len);

        if(read_bytes < 0) {
            perror("recvfrom failed");
            abort();
        }

        printf("Messge recived is %s\n",buffer);
    }

    close(sock);

    return 0;
}