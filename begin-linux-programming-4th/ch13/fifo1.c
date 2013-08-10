/*
 * \file fifo1.c
 * \brief create name pipes
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-08-08
 */
/* $Id$ */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int res = mkfifo("/tmp/my_fifo", 0777);
	if (res == 0) {
		printf("FIFO created\n");
	}
	exit(EXIT_SUCCESS);
}

