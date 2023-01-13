#include "rpc_data.h"

#define MAX_LENGTH 1024

char *generate_function(rpc_t *rpc_data);
char *generate_header(rpc_t *rpc_data);
char *request_handler_generator(rpc_t *rpc_data);
