#include <stdio.h>
#include <string.h>

#ifndef TIME
#define LEFT 4
#define TEXT "run(s)"
#else
#include <unistd.h>
#include <signal.h>
#define LEFT 20
#define TEXT "second(s)"
#endif


int main() {

    int left = LEFT;

    FILE* file = fopen("/tmp/trial.left", "r+");
    if (file) {
        fscanf(file, "%d", &left);
        fseek(file, 0, SEEK_SET);
    }
    else {
        file = fopen("/tmp/trial.left", "w");
    }
    fprintf(file, "%d ", --left);
    fclose(file);

    if (left < 0) {
        printf("buy a license pls\n");
        return 1;
    }

    printf("%d "TEXT" left\n", left);

#ifdef TIME
    if (!fork()) {
        for (pid_t ppid = getppid(); ppid == getppid();) {
            FILE* file = fopen("/tmp/trial.left", "r+");
            fprintf(file, "%d ", --left);
            fclose(file);
            if (left < 0) kill(ppid, SIGKILL);
            sleep(1);
        }
        return 0;
    }
#endif


    char *name = NULL;
    printf("> ");
    getline(&name, &(size_t){0}, stdin);

    file = fopen("/tmp/trial.data", "r+");
    if (!file) {
        file = fopen("/tmp/trial.data", "w");
    }

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) > 0) {
        if (strcmp(line, name)) continue;
        printf("request found in cache\n");
        goto exit;
    }

    fseek(file, 0, SEEK_END);
    fprintf(file, "%s", name);

    exit:
    fclose(file);

    return 0;
}
