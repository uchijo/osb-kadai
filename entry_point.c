#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gen_code.h"

int main(int argc, char *argv[]) {
    rpc_t_list *rpcs = parse_def(argv[1]);

    char *server_file = generate_server(rpcs);
    char *client_code = generate_client(rpcs);

    puts(client_code);
}
