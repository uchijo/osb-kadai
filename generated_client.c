#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void exit_with_error(char *errorMessage, int line, char *file);

char *get_result(char *message) {
    int port = 5000;
    char *ip = "127.0.0.1";
    int len = strlen(message);
    int sock;

    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        exit_with_error("", __LINE__, __FILE__);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        exit_with_error("", __LINE__, __FILE__);
    }

    if (send(sock, message, len, 0) != len) {
        exit_with_error("", __LINE__, __FILE__);
    }

    int num;
    char *buf = malloc(sizeof(char) * 512);
    if ((num = recv(sock, buf, 511, 0)) <= 0) {
        exit_with_error("", __LINE__, __FILE__);
    }

    buf[num] = '\0';

    close(sock);
    return buf;
}

int hoge(
    int a,
    int b,
    float c
) {
    char *message = malloc(sizeof(char) * 1024);
    sprintf(message, "hoge % d % d % f",a, b, c);
    char *retval = get_result(message);    int result = atoi(retval);
    free(retval);
    return result;
}

int main() {
    int a = 100;
    int b = 1;
    float c = 1.01;
    int result = hoge(a, b, c);
    printf("result : %d\n", result);
}
