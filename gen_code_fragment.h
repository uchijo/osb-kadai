#include "rpc_data.h"

#define MAX_LENGTH 1024

char *generate_function(rpc_t *rpc_data);
char *generate_header(rpc_t *rpc_data);
char *request_handler_generator(rpc_t *rpc_data);
void append_to_last(char *str, char *append, int max_length);
char *generate_handler_invoker(rpc_t *rpc_data);
