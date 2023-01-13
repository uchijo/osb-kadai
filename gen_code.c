#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gen_code_fragment.h"

#define FRAGMENT_LENGTH 2048

void exit_with_error(char *errorMessage, int line, char *file);

char *generate_server(rpc_t *rpc_data) {
    char *fragment1 = malloc(FRAGMENT_LENGTH * sizeof(char));
    fragment1 =
    ""
    ""
    "";

    puts(fragment1);
    return fragment1;
}
