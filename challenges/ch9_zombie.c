#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) {
        printf("[child] exiting immediately\n");
        _exit(0);
    } else {
        printf("[parent] sleeping, child should be zombie (check with 'ps aux | grep Z')\n");
        sleep(10); // During this time, child is a zombie
        waitpid(pid, NULL, 0);
        printf("[parent] collected child\n");
    }
    return 0;
}