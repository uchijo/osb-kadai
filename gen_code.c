#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gen_code.h"

void exit_with_error(char *errorMessage, int line, char *file);

char *generate_server(rpc_t *rpc_data) {
    char *fragment1 = malloc(FRAGMENT_LENGTH * sizeof(char));
    char *fragment2;

    fragment1[0] = '\0';
    fragment2 =
"#include <arpa/inet.h>\n"
"#include <stdio.h>\n"
"#include <stdlib.h>\n"
"#include <string.h>\n"
"#include <sys/socket.h>\n"
"#include <unistd.h>\n"
"\n"
"#include \"message_manager.h\"\n"
"\n"
"// headers for rpc functions\n\0"
;

    append_to_last(fragment1, fragment2, FRAGMENT_LENGTH);
    append_to_last(fragment1, generate_header(rpc_data), FRAGMENT_LENGTH);

    fragment2 =
""
"int main() {\n"
"    int port = 5000;\n"
"    struct sockaddr_in client;\n"
"    struct sockaddr_in server;\n"
"    int server_sock;\n"
"    int client_sock;\n"
"\n"
"    if ((server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {\n"
"        exit_with_error(\"unable to get socket server.\", __LINE__, __FILE__);\n"
"    }\n"
"\n"
"    server.sin_family = AF_INET;\n"
"    server.sin_addr.s_addr = htonl(INADDR_ANY);\n"
"    server.sin_port = htons(port);\n"
"\n"
"    if (bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0) {\n"
"        exit_with_error(\"failed to bind socket\", __LINE__, __FILE__);\n"
"    }\n"
"\n"
"    if (listen(server_sock, 5) < 0) {\n"
"        exit_with_error(\"\", __LINE__, __FILE__);\n"
"    }\n"
"\n"
"    for (;;) {\n"
"        int size = sizeof(client);\n"
"        if ((client_sock =\n"
"                 accept(server_sock, (struct sockaddr *)&client, &size)) < 0) {\n"
"            exit_with_error(\"\", __LINE__, __FILE__);\n"
"        }\n"
"\n"
"        client_handler(client_sock);\n"
"    }\n"
"    return 1;\n"
"}\n"
"\n"
;

    strcat(fragment1, fragment2);
    strcat(fragment1, request_handler_generator(rpc_data));

    fragment2 = 
"void client_handler(int sock) {\n"
"    char buf[1024];\n"
"    int mes_size;\n"
"\n"
"    if ((mes_size = recv(sock, buf, 1024, 0)) < 0) {\n"
"        exit_with_error(\"\", __LINE__, __FILE__);\n"
"    }\n"
"\n"
"    printf(\"message received: %s\\n\", buf);\n"
"\n"
"    func_call *func_data = decode_func_call(buf);\n"
"    // varies on .rpch file\n"
;
    strcat(fragment1, fragment2);

    // deal with handler invocation
    strcat(fragment1, generate_handler_invoker(rpc_data));

    fragment2 =
"    free_func_call(func_data);\n"
"\n"
"    printf(\"closing connection on socket %d\\n\", sock);\n"
"    close(sock);\n"
"    puts(\"closed!\\n\");\n"
"}\n"
"\n"
;
    strcat(fragment1, fragment2);

    return fragment1;
}
