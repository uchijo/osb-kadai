#include "gen_code_fragment.h"

#define FRAGMENT_LENGTH 4096

char *generate_server(rpc_t_list *rpc_data);
char *generate_client(rpc_t_list *rpc_data);
char *generate_server_template(rpc_t_list *rpc_data);
char *generate_client_header(rpc_t_list *rpc_data);
