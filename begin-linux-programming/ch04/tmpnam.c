/*
 * \file tmpnam.c
 * \brief demo for tmpnam and tmpfile
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-06
 */
/* $Id$ */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char tmpname[L_tmpnam];
	char *filename;
	FILE *tmpfp;

	filename = tmpnam(tmpname);

	printf("Temporary file name is %s\n", filename);
	tmpfp = tmpfile();
	if (tmpfp) {
		printf("Open a temporary file OK\n");
	} else {
		perror("tmpfile");
	}

	exit(0);
}

