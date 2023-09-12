#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 2*PATH_MAX+42
int check(const char* name) {
    static volatile char* sign = "~~llxkp";
    static char* raw = "sed 's/~>\\?llxkp/llxkp\\x0/' %s -i~\nrm %s~\n";
    char cmd[SIZE];
    snprintf(cmd, SIZE, raw, name, name);
    return system(cmd) || sign[0] != '~';
}

int main(int argc, char** argv) {
    printf(check(argv[0])?":(\n":":)\n");
    return 0;
}
