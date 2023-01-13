#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void exit_with_error(char *errorMessage, int line, char *file);
void handle_client(int sock);

// generated
int sum(int a, int b) {
    printf("called\n");
    return a + b;
}

int main() {
    int port = 5000;
    struct sockaddr_in client;
    struct sockaddr_in server;
    int server_sock;
    int client_sock;

    if ((server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        exit_with_error("unable to get socket server.", __LINE__, __FILE__);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    if (bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        exit_with_error("failed to bind socket", __LINE__, __FILE__);
    }

    if (listen(server_sock, 5) < 0) {
        exit_with_error("", __LINE__, __FILE__);
    }

    for (;;) {
        int size = sizeof(client);
        if ((client_sock =
                 accept(server_sock, (struct sockaddr *)&client, &size)) < 0) {
            exit_with_error("", __LINE__, __FILE__);
        }

        handle_client(client_sock);
    }
    return 1;
}

void handle_client(int sock) {
    char buf[300];
    int mes_size;

    if ((mes_size = recv(sock, buf, 300, 0)) < 0) {
        exit_with_error("", __LINE__, __FILE__);
    }

    printf("message received: %s\n", buf);

    while (mes_size > 0) {
        // parse
        char *token;
        int result;
        int a;
        int b;

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
            exit_with_error("", __LINE__, __FILE__);
        }

        if ((mes_size = recv(sock, buf, 300, 0)) < 0) {
            exit_with_error("", __LINE__, __FILE__);
        }
    }

    printf("closed connection on socket %d\n\n", sock);

    close(sock);
}

void handle_client2(int sock) {
    char buf[300];
    int mes_size;

    if ((mes_size = recv(sock, buf, 300, 0)) < 0) {
        exit_with_error("", __LINE__, __FILE__);
    }

    printf("message received: %s\n", buf);

    // varies on .rpch file
    

    printf("closing connection on socket %d\n\n", sock);
    close(sock);
    printf("closed!");
}
