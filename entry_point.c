#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gen_code.h"
#include "manage_file.h"

int main(int argc, char *argv[]) {
    rpc_t_list *rpcs = parse_def(argv[1]);

    char *server_file = generate_server(rpcs);
    char *client_file = generate_client(rpcs);

    char *server_template = generate_server_template(rpcs);
    char *client_header = generate_client_header(rpcs);

    generate_file("gen/server/server_gen.c", server_file);
    generate_file("gen/client/client_gen.c", client_file);

    generate_file("gen/server/server_template.c", server_template);
    generate_file("gen/client/client_header.h", client_header);
}
