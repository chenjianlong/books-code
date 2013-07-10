/*
 * \file lock1.c
 * \brief creating a lock file
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-03
 */
/* $Id$ */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
	int file_desc;
	int save_errno;

	file_desc = open("/tmp/LCK.test", O_RDWR | O_CREAT | O_EXCL, 0444);
	if (file_desc == -1) {
		save_errno = errno;
		printf("Open failed with error %d\n", save_errno);
	} else {
		printf("Open succeeded\n");
	}
	exit(EXIT_SUCCESS);
}

