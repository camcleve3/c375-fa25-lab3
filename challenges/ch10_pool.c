#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <max_concurrency> <file1> [file2 ...]\n", argv[0]);
        return 1;
    }
    int max_concurrency = atoi(argv[1]);
    int num_tasks = argc - 2;
    int running = 0, next = 0;
    pid_t pids[num_tasks];

    while (next < num_tasks || running > 0) {
        // Spawn new workers if below concurrency limit and tasks remain
        while (running < max_concurrency && next < num_tasks) {
            pid_t pid = fork();
            if (pid < 0) { perror("fork"); exit(1); }
            if (pid == 0) {
                printf("[worker] PID=%d working on %s\n", getpid(), argv[next + 2]);
                sleep(2); // Simulate work
                printf("[worker] PID=%d finished %s\n", getpid(), argv[next + 2]);
                _exit(0);
            } else {
                pids[next] = pid;
                running++;
                next++;
            }
        }
        // Wait for any child to finish
        int status;
        pid_t done = wait(&status);
        if (done > 0) {
            running--;
            printf("[parent] Worker PID=%d exited\n", done);
        }
    }
    return 0;
}