#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    if (pipe(fd) == -1) { perror("pipe"); exit(1); }

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) {
        // Child: read numbers and sum
        close(fd[1]);
        FILE *in = fdopen(fd[0], "r");
        int sum = 0, num;
        while (fscanf(in, "%d", &num) == 1) {
            sum += num;
        }
        fclose(in);
        printf("Child: sum = %d\n", sum);
        _exit(0);
    } else {
        // Parent: write numbers
        close(fd[0]);
        FILE *out = fdopen(fd[1], "w");
        for (int i = 1; i <= 10; i++) {
            fprintf(out, "%d\n", i);
        }
        fclose(out);
        waitpid(pid, NULL, 0);
    }
    return 0;
}