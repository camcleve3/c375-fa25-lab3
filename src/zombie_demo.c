#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) {
        printf("[child] exiting\n");
        _exit(0);
    } else {
        printf("[parent] sleeping, child should be zombie\n");
        sleep(10); // Check with 'ps aux | grep Z'
        waitpid(pid, NULL, 0);
        printf("[parent] collected child\n");
    }
    return 0;
}