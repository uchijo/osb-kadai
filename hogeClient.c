#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void error_message(int line);

int main() {
    int port = 5000;
    char *mes = "100 1";
    char *ip = "127.0.0.1";
    int len = strlen(mes);
    int sock;

    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        error_message(__LINE__);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        error_message(__LINE__);
    }

    if (send(sock, mes, len, 0) != len) {
        error_message(__LINE__);
    }

    printf("RECEIVED: ");
    int total = 0;
    int num;
    char buf[50];
    while (total < len) {
        if ((num = recv(sock, buf, 49, 0)) <= 0) {
            error_message(__LINE__);
        }

        total += num;
        buf[num] = '\0';
        printf("%s", buf);
    }

    printf("\n");
    close(sock);
    exit(1);
    return 1;
}

void error_message(int line) {
    printf("ERROR: LINE %d", line);
    exit(1);
}
