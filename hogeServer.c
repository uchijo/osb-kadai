#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

void error_message(int line);
void handle_client(int sock);

// generated
int sum(int a, int b);

int main() {
    int port = 5000;
    struct sockaddr_in client;
    struct sockaddr_in server;
    int server_sock;
    int client_sock;

    if ((server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        error_message(__LINE__);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    if (bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        error_message(__LINE__);
    }

    if (listen(server_sock, 5) < 0) {
        error_message(__LINE__);
    }

    for (;;) {
        int size = sizeof(client);
        if ((client_sock = accept(server_sock, (struct sockaddr *)&client, &size)) < 0) {
            error_message(__LINE__);
        }

        handle_client(client_sock);
    }
    return 1;
}

void handle_client(int sock) {
    char buf[300];
    int mes_size;

    if ((mes_size = recv(sock, buf, 300, 0)) < 0) {
        error_message(__LINE__);
    }

    printf("message received: %s\n", buf);

    while (mes_size > 0) {
        // parse
        char *token;
        int result;
        int a; int b;

        token = strtok(buf, " ");
        printf("token for a: %s\n", token);
        a = atoi(token);

        token = strtok(NULL, " ");
        printf("token for b: %s\n", token);
        b = atoi(token);

        // execution
        result = sum(a, b);

        sprintf(buf, "%d", result);
        printf("a: %d, b: %d\n", a, b);
        printf("result: %d\n", result);
        printf("result string: %s\n", buf);

        if (send(sock, buf, mes_size, 0) != mes_size) {
            error_message(__LINE__);
        }

        if ((mes_size = recv(sock, buf, 300, 0)) < 0) {
            error_message(__LINE__);
        }
    }

    printf("closed connection on socket %d\n\n", sock);

    close(sock);
}

void error_message(int line) {
    printf("ERROR: LINE %d", line);
    exit(1);
}

int sum(int a, int b) {
    printf("called\n");
    return a+b;
}
