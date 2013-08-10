/*
 * \file popen3.c
 * \brief reading larger amounts of data from a Pipe
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-08-01
 */
/* $Id$ */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	FILE *read_fp;
	char buffer[BUFSIZ + 1];
	int chars_read;

	memset(buffer, '\0', sizeof(buffer));
	read_fp = popen("ps ax", "r");
	if (read_fp != NULL) {
		chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
		while (chars_read > 0) {
			buffer[chars_read] = '\0';
			printf("Reading %d:-\n %s\n", BUFSIZ, buffer);
			chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
		}
		fclose(read_fp);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}

