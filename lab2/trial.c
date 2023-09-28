#include <stdio.h>
#define LEFT 2


int main() {

    int left = LEFT;

    FILE* file = fopen("/tmp/trial", "r+");
    if (file) {
        fscanf(file, "%d", &left);
        fseek(file, 0, SEEK_SET);
    }
    else {
        file = fopen("/tmp/trial", "w");
    }
    fprintf(file, "%d", --left);
    fclose(file);

    if (left < 0) {
        printf("buy a license pls\n");
        return 1;
    }

    printf("%d runs left\n", left);
    return 0;
}
