/*
 * \file memory1.c
 * \brief demo for alloc memory
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-02
 */
/* $Id$ */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define A_MEGABYTE (1024 * 1024)

int main()
{
	char *some_memory;
	int megabyte = A_MEGABYTE;
	int exit_code = EXIT_FAILURE;

	some_memory = (char *)malloc(megabyte);
	if (some_memory != NULL) {
		sprintf(some_memory, "Hello World\n");
		printf("%s", some_memory);
		exit_code = EXIT_SUCCESS;
	}
	exit(exit_code);
}

