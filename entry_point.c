#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gen_code_fragment.h"

int main(int argc, char *argv[]) {
    char_list *list = read_file(argv[1]);

    int start_index = index_of(list, "{\n");
    int end_index = index_of(list, "}\n");

    char_list *new_list = sublist(list, start_index+1, end_index-1);

    rpc_t *rpc = create_rpc_t_from_tokens(new_list);

    char *func_result = generate_function(rpc);
    char *header_result = generate_header(rpc);
    char *handler_result = request_handler_generator(rpc);
    puts(func_result);
    puts(handler_result);
}
