#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rpc_data.h"

rpc_t *create_rpc_t_from_tokens(char_list *list) {
    rpc_t *rpc = malloc(sizeof(rpc_t));

    // function name
    rpc->name = malloc(strlen(get_string(list, 0)));
    char_list *name_list = split_string(get_string(list, 0), " /\n");
    strcpy(rpc->name, get_string(name_list, 1));
    free_list(name_list);

    // return type
    rpc->return_type = malloc(strlen(get_string(list, 1)));
    char_list *return_type_list = split_string(get_string(list, 1), " /\n");
    strcpy(rpc->return_type, get_string(return_type_list, 1));
    free_list(return_type_list);

    rpc->args_length = length(list) - 2;
    rpc->args = malloc(sizeof(arg_t) * rpc->args_length);
    for (int i = 0; i < rpc->args_length; i++) {
        char_list *tokens = split_string(get_string(list, i + 2), " /\n");

        rpc->args[i].type = malloc(strlen(get_string(tokens, 1)));
        strcpy(rpc->args[i].type, get_string(tokens, 1));

        rpc->args[i].name = malloc(strlen(get_string(tokens, 2)));
        strcpy(rpc->args[i].name, get_string(tokens, 2));

        free_list(tokens);
    }
    return rpc;
}

void print_rpc_t(rpc_t *rpc) {
    printf("name: %s\n", rpc->name);
    printf("return type: %s\n", rpc->return_type);
    printf("args length: %d\n", rpc->args_length);
    for (int i = 0; i < rpc->args_length; i++) {
        printf("arg %d: %s %s\n", i, rpc->args[i].type, rpc->args[i].name);
    }
}

rpc_t_list *parse_def(char *path) {
    char_list *list = read_file(path);
    rpc_t_list *rpcs = malloc(sizeof(rpc_t *));
    rpcs->rpc = malloc(sizeof(rpc_t **));
    rpcs->length = 0;

    while(length(list) > 5) {
        int start_index = index_of(list, "{\n");
        int end_index = index_of(list, "}\n");

        char_list *new_list = sublist(list, start_index+1, end_index-1);
        rpcs->rpc = realloc(rpcs->rpc, sizeof(rpc_t *) * (rpcs->length + 1));
        rpcs->rpc[rpcs->length] = create_rpc_t_from_tokens(new_list);
        rpcs->length++;

        list = sublist(list, end_index+1, length(list)-1);
    }

    free_list(list);

    return rpcs;
}
