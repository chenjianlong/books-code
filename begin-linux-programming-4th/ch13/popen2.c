/*
 * \file popen2.c
 * \brief sending output to an external program
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-08-04
 */
/* $Id$ */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	FILE *write_fp;
	char buffer[BUFSIZ + 1];

	sprintf(buffer, "Once upon a time, there was...\n");
	write_fp = popen("od -c", "w");
	if (write_fp != NULL) {
		fwrite(buffer, sizeof(char), strlen(buffer), write_fp);
		pclose(write_fp);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}

