#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gen_code.h"

void exit_with_error(char *errorMessage, int line, char *file);
void append_to_last(char *str, char *append);

char *generate_function(rpc_t *rpc_data) {
    char *first_line = malloc(MAX_LENGTH * sizeof(char));
    char buf[256];

    sprintf(first_line, "%s %s(\n", rpc_data->return_type, rpc_data->name);

    for (int i=0; i<rpc_data->args_length; i++) {
        if (i==rpc_data->args_length-1) {
            sprintf(buf, "  %s %s\n", rpc_data->args[i].type, rpc_data->args[i].name);
            append_to_last(first_line, buf);
            append_to_last(first_line, ") {\n");
            append_to_last(first_line, "  // TODO: implement this function\n");
            append_to_last(first_line, "}\n");
            break;
        }
        sprintf(buf, "  %s %s,\n" , rpc_data->args[i].type, rpc_data->args[i].name);
        append_to_last(first_line, buf);
    }

    return first_line;
}

char *generate_header(rpc_t *rpc_data) {
    char *first_line = malloc(MAX_LENGTH * sizeof(char));
    char buf[256];

    sprintf(first_line, "%s %s(\n", rpc_data->return_type, rpc_data->name);

    for (int i=0; i<rpc_data->args_length; i++) {
        if (i==rpc_data->args_length-1) {
            sprintf(buf, "  %s %s\n", rpc_data->args[i].type, rpc_data->args[i].name);
            append_to_last(first_line, buf);
            append_to_last(first_line, ");\n");
            break;
        }
        sprintf(buf, "  %s %s,\n" , rpc_data->args[i].type, rpc_data->args[i].name);
        append_to_last(first_line, buf);
    }

    return first_line;
}

void append_to_last(char *str, char *append) {
    int str_length = strlen(str);
    int append_length = strlen(append);

    if (str_length + append_length > MAX_LENGTH) {
        exit_with_error("String too long", __LINE__, __FILE__);
    }
    for (int i=0; i<append_length; i++) {
        str[str_length+i] = append[i];
    }
    str[str_length+append_length] = '\0';
}
