#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int mysystem(char *command)
{
    pid_t pid = fork();
    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command, (char*) NULL);
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        int status = 0;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }

        return status;
    } else {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <command>\n", argv[1]);
        exit(1);
    }

    int n = mysystem(argv[1]);
    printf("mysystem return: %d\n", n);
    return n;
}
