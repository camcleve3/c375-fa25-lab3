#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("worker: argc=%d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("worker: argv[%d]=%s\n", i, argv[i]);
    }
    char *myvar = getenv("MYVAR");
    printf("worker: MYVAR=%s\n", myvar ? myvar : "(not set)");
    return 0;
}