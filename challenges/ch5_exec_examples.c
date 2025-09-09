#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid1 = fork();
    if (pid1 < 0) { perror("fork"); exit(1); }
    if (pid1 == 0) {
        // Child A: execl
        execl("/bin/echo", "echo", "one", (char *)NULL);
        perror("execl");
        _exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) { perror("fork"); exit(1); }
    if (pid2 == 0) {
        // Child B: execv
        char *args[] = {"echo", "one", NULL};
        execv("/bin/echo", args);
        perror("execv");
        _exit(1);
    }

    // Parent waits for both
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}