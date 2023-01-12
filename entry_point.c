#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "char_list.h"
#include "rpc_data.h"

int main(int argc, char *argv[]) {
    char_list *list = read_file(argv[1]);

    int start_index = index_of(list, "{\n");
    int end_index = index_of(list, "}\n");

    char_list *new_list = sublist(list, start_index+1, end_index-1);
    print_list(new_list);
    puts("");

    char_list *tokens = split_string(get_string(new_list, 0), " ");
    print_list(tokens);
}
