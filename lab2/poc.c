#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define TRIAL 3


void copy(const char* src, const char* dst) {
    pid_t pid = fork();
    if (pid)
        waitpid(pid, 0, 0);
    else
        execl("/bin/cp", "/bin/cp", src, dst, NULL);
}

int find_magic(FILE* file) {
    volatile int magic = 0xde00;
    int var = 0;
    magic |= 0xad;
    while (!feof(file) && fread(&var, 2, 1, file))
        if (var == magic) return 0;
    return 1;
}

void check() {
    static volatile int hp = TRIAL << 16 | 0xdead;

    if (!(hp >> 16)) exit(EXIT_FAILURE);

    copy("poc", "poc_");
    FILE* self = fopen("poc_", "rb+");

    int r = find_magic(self);

    unsigned int var = 0;
    fread(&var, 1, 1, self);
    fseek(self, -1, SEEK_CUR);
    --var;
    fwrite(&var, 1, 1, self);

    fclose(self);
    rename("poc_", "poc");
}


int main() {
    check();
    printf("yeah\n");
    return 0;
}
