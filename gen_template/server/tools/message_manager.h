#include "char_list.h"

// a struct that represents function call
typedef struct {
    char *name;
    char_list *value;
} func_call;


func_call *decode_func_call(char *str);
void print_func_call(func_call *call);
void free_func_call(func_call *call);
char *encode_func_call(func_call *call);
