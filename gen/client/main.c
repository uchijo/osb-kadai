#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "client_header.h"

int main() {
    int hoge_result = hoge(1, 2, 3.0);
    float fuga_result = fuga(5.0, 2.0);
    char *piyo_result = piyo("hello, ", "world!");
    int bar_result = bar(100);
    printf("hoge_result: %d\n", hoge_result);
    printf("fuga_result: %f\n", fuga_result);
    printf("piyo_result: %s\n", piyo_result);
    printf("bar_result: %d\n", bar_result);
}
