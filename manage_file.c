#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exit_with_error(char *errorMessage, int line, char *file);

void generate_file(char *path, char *content) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        exit_with_error("Error opening file", __LINE__, __FILE__);
    }
    fprintf(file, "%s", content);
    fclose(file);
}
