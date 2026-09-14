#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


unsigned int snooze(unsigned int secs)
{
	unsigned int n = sleep(secs);
	printf("Slept for %u of %u secs.\n", (secs - n), secs);
	return n;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: %s <secs>\n", argv[0]);
		exit(1);
	}

	snooze(atoi(argv[1]));
	return 0;
}
