/*
 * \file pipe3.c
 * \brief pipes across a fork and exec
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-08-05
 */
/* $Id$ */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int data_processed;
	int file_pipes[2];
	const char some_data[] = "123";
	char buffer[BUFSIZ + 1];
	pid_t fork_result;

	memset(buffer, '\0', sizeof(buffer));

	if (pipe(file_pipes) == 0) {
		fork_result = fork();
		if (fork_result == -1) {
			fprintf(stderr, "Fork failure");
			exit(EXIT_FAILURE);
		}

		if (fork_result == 0) {
			sprintf(buffer, "%d", file_pipes[0]);
			execl("pipe4", "pipe4", buffer, (char *)0);
			exit(EXIT_SUCCESS);
		} else {
			data_processed = write(file_pipes[1], some_data, strlen(some_data));
			printf("%d - Wrote %d bytes\n", getpid(), data_processed);
		}
	}
	exit(EXIT_SUCCESS);
}

