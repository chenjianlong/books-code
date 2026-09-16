#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>

void handler(int sig) {
}

char *tfgets(char *str, int size, FILE *restrict stream)
{
    struct sigaction sa = { .sa_handler = handler };
    sigemptyset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);

    struct itimerval timer = {
        .it_value    = { .tv_sec = 5, .tv_usec = 0 },
        .it_interval = { .tv_sec = 0, .tv_usec = 0 }
    };

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(1);
    }

    char* rc = fgets(str, size, stream);
    struct itimerval zero = {0};
    setitimer(ITIMER_REAL, &zero, NULL);
    return rc;
}

int main(int argc, char *argv[])
{
    char buf[80];
    while (1) {
        char *rc = tfgets(buf, sizeof(buf), stdin);
        if (rc == NULL) {
            printf("tgets return NULL\n");
        } else {
            printf("tgets return %s\n", rc);
        }
    }
    return 0;
}