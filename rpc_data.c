#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rpc_data.h"
#include "char_list.h"

rpc_t *create_rpc(char_list *list) {
    rpc_t *rpc = malloc(sizeof(rpc_t));
    rpc->name = get_string(list, 0);
    rpc->return_type = get_string(list, 1);
    rpc->args_length = length(list) - 2;
    rpc->args = malloc(sizeof(arg_t) * rpc->args_length);
    for (int i = 0; i < rpc->args_length; i++) {
        char *arg = get_string(list, i + 2);
        char *type = strtok(arg, " ");
        char *name = strtok(NULL, " ");
        rpc->args[i].type = type;
        rpc->args[i].name = name;
    }
    return rpc;
}
