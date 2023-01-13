#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int hoge(
    int a,
    int b,
    float c
) {
    // TODO: implement this function
    return a + b;
}

float fuga(
    float aaa,
    float bbbb
) {
    // TODO: implement this function
    return aaa/bbbb;
}

char* piyo(
    char* test,
    char* testtest
) {
    // TODO: implement this function
    int size = strlen(test) + strlen(testtest);
    char *retval = malloc(sizeof(char) * size);
    sprintf(retval, "%s%s", test, testtest);
    return retval;
}

int bar(
    int test
) {
    // TODO: implement this function
    return 1;
}

