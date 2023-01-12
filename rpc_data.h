#include "char_list.h"

typedef struct {
    char *type;
    char *name;
} arg_t;

typedef struct {
    char *name;
    char *return_type;
    arg_t *args;
    int args_length;
} rpc_t;

rpc_t *create_rpc_t_from_tokens(char_list *list);
void print_rpc_t(rpc_t *rpc);
