/*
 * \file memory4.c
 * \brief try to do "bad" things with memory, allocate memory and then attempt to write past the end
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-03
 */
/* $Id$ */

#include <stdlib.h>

#define ONE_K (1024)

int main()
{
	char *some_memory;
	char *scan_ptr;

	some_memory = (char *)malloc(ONE_K);
	if (some_memory == NULL) {
		exit(EXIT_FAILURE);
	}

	scan_ptr = some_memory;
	while (1) {
		*scan_ptr = '\0';
		scan_ptr++;
	}
	exit(EXIT_SUCCESS);
}

