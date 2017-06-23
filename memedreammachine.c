#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static int soc;

static void exitmessage() {
    close(soc);
    printf("rip");
}

int main(void) {
    atexit(exitmessage);
    struct sockaddr_in rec;
    char* messages[] = {"circular", "reasoning", "works", "because"};
    soc =  socket(AF_INET, SOCK_DGRAM, 0);
    rec.sin_family = AF_INET;
    rec.sin_port = htons(1100);
    inet_aton("127.0.0.1", &rec.sin_addr.s_addr);
    for(int i = 0; i<4; ++i) {
        sendto(soc, messages[i], strlen(messages[i]), 0, &rec, sizeof rec);
        if(i == 3) i = 0;
    }
    return 0;
}
