#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

unsigned int snooze(unsigned int secs)
{
	unsigned int n = sleep(secs);
	printf("Slept for %u of %u secs.\n", (secs - n), secs);
	return n;
}

void handler(int sig) /* SIGINT handler */
{
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: %s <secs>\n", argv[0]);
		exit(1);
	}

    if (signal(SIGINT, handler) == SIG_ERR) {
        int e = errno;
        printf("Failed to signal SIGINT, err=%d, %s\n", e, strerror(e));
        exit(1);
    }

	snooze(atoi(argv[1]));
	return 0;
}
