#include <stdio.h>
#include <stdlib.h>

int check() {
    static volatile char* sign = "~~llxkp";
    system("sed 's/~>\\?llxkp/llxkp\\x0/' poc -i~\nrm poc~\n");
    return sign[0] == '~';
}

int main() {
    printf(check()?":)\n":":(\n");
    return 0;
}
