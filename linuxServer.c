#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>


int main() {
    struct sockaddr_in addr;
    char buffer[1024];
    ssize_t recsize;
    socklen_t fromlen;

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1100);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    fromlen = sizeof addr;

    if (bind(sock, (struct sockaddr *)&addr, sizeof addr) == -1) {
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Server running ...\n");

    for (;;) {
        recsize = recvfrom(sock, (void *)buffer, sizeof buffer, 0, (struct sockaddr *)&addr, &fromlen);
        printf("recsize: %d\n", (int)recsize);
        sleep(1);
        printf("datagra: %.*s\n", (int)recsize, buffer);
    }

    close(sock);
}

