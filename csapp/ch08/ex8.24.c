#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#define N 2
static const char buf[2] = "a";

int main()
{
    int status, i;
    pid_t pid;

    /* Parent creates N children */
    for (i = 0; i < N; i++) {
        if ((pid = fork()) == 0) {
            /* Child */
            *((char*)&buf[0]) = 'b';
            exit(100+i);
        }
    }

    /* Parent reaps N children in no particular order */
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            printf("child %d terminated normally with exit status=%d\n",
                    pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            int signo = WTERMSIG(status);
            printf("child %d terminated by signal %d: %s\n",
                    pid, signo, strsignal(signo));
        } else {
            printf("child %d terminated abnormally\n", pid);
        }
    }

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD) {
        perror("waitpid error");
        exit(EXIT_FAILURE);
    }

    exit(0);
}