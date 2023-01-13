#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "message_manager.h"

// a function that decodes a function call from a string
// string format is: "function_name arg1_value arg2_value ..."
func_call *decode_func_call(char *str) {
    func_call *call = malloc(sizeof(func_call));
    char_list *list = split_string(str, " /\n");
    call->name = malloc(strlen(get_string(list, 0)) + 1);
    strcpy(call->name, get_string(list, 0));
    call->value = sublist(list, 1, length(list) - 1);
    free_list(list);
    return call;
}

// a function that prints a function call
void print_func_call(func_call *call) {
    printf("name: %s\n", call->name);
    printf("value: ");
    for (int i = 0; i < length(call->value); i++) {
        printf("%s ", get_string(call->value, i));
    }
}

// a function that frees a function call
void free_func_call(func_call *call) {
    free(call->name);
    free_list(call->value);
    free(call);
}

// a function that encodes a function call to a string
// string format is: "function_name arg1_value arg2_value ..."
char *encode_func_call(func_call *call) {
    char *str = malloc(strlen(call->name) + 1);
    strcpy(str, call->name);
    for (int i = 0; i < length(call->value); i++) {
        char *arg = get_string(call->value, i);
        str = realloc(str, strlen(str) + strlen(arg) + 2);
        strcat(str, " ");
        strcat(str, arg);
    }
    return str;
}
