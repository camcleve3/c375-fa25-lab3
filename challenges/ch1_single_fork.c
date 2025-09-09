#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) {
        printf("Hello from child (PID=%d, PPID=%d)\n", getpid(), getppid());
        sleep(2);
        _exit(42);
    } else {
        int status;
        waitpid(pid, &status, 0);
        printf("Parent: child exited with status %d\n", WEXITSTATUS(status));
    }
    return 0;
}