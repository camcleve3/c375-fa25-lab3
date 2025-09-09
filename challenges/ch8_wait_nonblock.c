#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pids[3];
    int sleep_times[3] = {1, 2, 3};
    int finished[3] = {0, 0, 0};

    // Fork 3 children
    for (int i = 0; i < 3; i++) {
        pids[i] = fork();
        if (pids[i] < 0) { perror("fork"); exit(1); }
        if (pids[i] == 0) {
            sleep(sleep_times[i]);
            printf("[child %d] done\n", i);
            _exit(10 + i);
        }
    }

    int remaining = 3;
    while (remaining > 0) {
        for (int i = 0; i < 3; i++) {
            if (!finished[i]) {
                int status;
                pid_t result = waitpid(pids[i], &status, WNOHANG);
                if (result == pids[i]) {
                    printf("[parent] child %d (PID=%d) exited with status %d\n", i, pids[i], WEXITSTATUS(status));
                    finished[i] = 1;
                    remaining--;
                }
            }
        }
        sleep(1); // Poll every second
    }
    return 0;
}