#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gen_code_fragment.h"

void exit_with_error(char *errorMessage, int line, char *file);
void append_to_last(char *str, char *append);
char *gen_type_parser(arg_t *arg);

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

char *request_handler_generator(rpc_t *rpc_data) {
    char *first_line = malloc(MAX_LENGTH * sizeof(char));
    char buf[256];

    sprintf(first_line, "char *handle_%s (char *message) {\n", rpc_data->name);
    append_to_last(first_line, "    func_call *func_data = decode_func_call(message);\n");
    append_to_last(first_line, "    char *retval = malloc(sizeof(char) * 1024);\n");
    append_to_last(first_line, "\n");
    append_to_last(first_line, "    // varies depending on the function\n");
    sprintf(buf, "    %s result = %s(\n", rpc_data->return_type, rpc_data->name);
    append_to_last(first_line, buf);
    
    // manage arguments
    for (int i=0; i<rpc_data->args_length; i++) {
        if (i==rpc_data->args_length-1) {
            sprintf(buf, "        %s(get_string(func_data->value, %d))\n", gen_type_parser(&(rpc_data->args[i])), i);
            append_to_last(first_line, buf);
            append_to_last(first_line, "    );\n");
            append_to_last(first_line, "\n");
            break;
        }
        sprintf(buf, "        %s(get_string(func_data->value, %d)),\n", gen_type_parser(&(rpc_data->args[i])), i);
        append_to_last(first_line, buf);
    }

    append_to_last(first_line, "    free_func_call(func_data);\n");
    append_to_last(first_line, "    return retval;\n");
    append_to_last(first_line, "}\n");

    return first_line;
}

char *gen_type_parser(arg_t *arg) {
    if (strcmp(arg->type, "int") == 0) {
        return "atoi";
    }
    if (strcmp(arg->type, "float") == 0) {
        return "atof";
    }
    if (strcmp(arg->type, "char") == 0) {
        return "";
    }

    // default
    printf("given type: %s\n", arg->type);
    exit_with_error("Unknown type", __LINE__, __FILE__);
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
