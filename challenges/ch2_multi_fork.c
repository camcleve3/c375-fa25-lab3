#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_children>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    pid_t pids[n];

    for (int i = 0; i < n; i++) {
        pids[i] = fork();
        if (pids[i] < 0) { perror("fork"); exit(1); }
        if (pids[i] == 0) {
            printf("Child %d (PID=%d) running\n", i, getpid());
            sleep(1);
            _exit(i + 10);
        }
    }

    for (int i = 0; i < n; i++) {
        int status;
        pid_t pid = waitpid(pids[i], &status, 0);
        printf("Parent: child %d (PID=%d) exited with status %d\n", i, pid, WEXITSTATUS(status));
    }
    return 0;
}