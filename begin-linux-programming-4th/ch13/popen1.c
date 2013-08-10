/*
 * \file popen1.c
 * \brief demo for reading output from an external program
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
	FILE *read_fp;
	char buffer[BUFSIZ + 1];
	int chars_read;
	memset(buffer, '\0', sizeof(buffer));
	read_fp = popen("uname -a", "r");
	if (read_fp != NULL) {
		chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
		if (chars_read > 0) {
			printf("Output was:-\n%s\n", buffer);
		}
		pclose(read_fp);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}

