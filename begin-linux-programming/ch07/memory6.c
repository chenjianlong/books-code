/*
 * \file memory6.c
 * \brief free memory
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-03
 */
/* $Id$ */

#include <stdlib.h>
#include <stdio.h>

#define ONE_K (1024)

int main()
{
	char *some_memory;
	int exit_code = EXIT_FAILURE;

	some_memory = (char *)malloc(ONE_K);
	if (some_memory != NULL) {
		free(some_memory);
		printf("Memory allocated and free again\n");
		exit_code = EXIT_SUCCESS;
	}
	exit(exit_code);
}

