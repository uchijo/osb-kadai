#include <stdio.h>  /* for perror() */
#include <stdlib.h> /* for exit() */

void exit_with_error(char *errorMessage, int line, char *file) {
    printf("Error at line %d in %s", line, file);
    perror(errorMessage);
    exit(1);
}
