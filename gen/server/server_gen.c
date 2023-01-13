#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "tools/message_manager.h"

// headers for rpc functions
int hoge(
    int a,
    int b,
    float c
);
float fuga(
    float aaa,
    float bbbb
);
char* piyo(
    char* test,
    char* testtest
);
int bar(
    int test
);
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

        client_handler(client_sock);
    }
    return 1;
}

char *handle_hoge (char *message) {
    func_call *func_data = decode_func_call(message);
    char *retval = malloc(sizeof(char) * 1024);

    // varies depending on the function
    int result = hoge(
        atoi(get_string(func_data->value, 0)),
        atoi(get_string(func_data->value, 1)),
        atof(get_string(func_data->value, 2))
    );

    sprintf(retval, "%d", result);
    free_func_call(func_data);
    return retval;
}
char *handle_fuga (char *message) {
    func_call *func_data = decode_func_call(message);
    char *retval = malloc(sizeof(char) * 1024);

    // varies depending on the function
    float result = fuga(
        atof(get_string(func_data->value, 0)),
        atof(get_string(func_data->value, 1))
    );

    sprintf(retval, "%f", result);
    free_func_call(func_data);
    return retval;
}
char *handle_piyo (char *message) {
    func_call *func_data = decode_func_call(message);
    char *retval = malloc(sizeof(char) * 1024);

    // varies depending on the function
    char* result = piyo(
        (get_string(func_data->value, 0)),
        (get_string(func_data->value, 1))
    );

    sprintf(retval, "%s", result);
    free_func_call(func_data);
    return retval;
}
char *handle_bar (char *message) {
    func_call *func_data = decode_func_call(message);
    char *retval = malloc(sizeof(char) * 1024);

    // varies depending on the function
    int result = bar(
        atoi(get_string(func_data->value, 0))
    );

    sprintf(retval, "%d", result);
    free_func_call(func_data);
    return retval;
}
void client_handler(int sock) {
    char buf[1024];
    int mes_size;

    if ((mes_size = recv(sock, buf, 1024 * sizeof(char), 0)) < 0) {
        exit_with_error("", __LINE__, __FILE__);
    }
    buf[mes_size] = '\0';

    printf("message received: %s\n", buf);

    func_call *func_data = decode_func_call(buf);
    // varies on .rpch file
    if (strcmp(func_data->name, "hoge") == 0) {
        char *retval = handle_hoge(buf);
        send(sock, retval, strlen(retval), 0);
        free(retval);
    }
    if (strcmp(func_data->name, "fuga") == 0) {
        char *retval = handle_fuga(buf);
        send(sock, retval, strlen(retval), 0);
        free(retval);
    }
    if (strcmp(func_data->name, "piyo") == 0) {
        char *retval = handle_piyo(buf);
        send(sock, retval, strlen(retval), 0);
        free(retval);
    }
    if (strcmp(func_data->name, "bar") == 0) {
        char *retval = handle_bar(buf);
        send(sock, retval, strlen(retval), 0);
        free(retval);
    }
    free_func_call(func_data);

    printf("closing connection on socket %d\n", sock);
    close(sock);
    puts("closed!\n");
}

