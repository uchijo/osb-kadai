#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void exit_with_error(int line);

int main() {
    int port = 5000;
    char *mes = "hoge 100 1 1.01";
    char *ip = "127.0.0.1";
    int len = strlen(mes);
    int sock;

    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        exit_with_error(__LINE__);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        exit_with_error(__LINE__);
    }
    puts("connected.");

    if (send(sock, mes, len, 0) != len) {
        exit_with_error(__LINE__);
    }

    printf("RECEIVED: ");
    int num;
    char buf[50];
    if ((num = recv(sock, buf, 49, 0)) <= 0) {
        exit_with_error(__LINE__);
    }

    buf[num] = '\0';
    printf("%s", buf);

    printf("\n");
    close(sock);
    return 1;
}

void exit_with_error(int line) {
    printf("ERROR: LINE %d", line);
    exit(1);
}
