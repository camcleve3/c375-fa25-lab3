#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) {
        printf("[child] running ls -la\n");
        execlp("ls", "ls", "-la", (char *)NULL);
        perror("execlp");
        _exit(1);
    } else {
        waitpid(pid, NULL, 0);
        printf("[parent] child finished\n");
    }
    return 0;
}