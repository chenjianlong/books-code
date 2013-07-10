/*
 * \file memory5a.c
 * \brief accessing a null pointer
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-03
 */
/* $Id$ */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	char *some_memory = (char *)0;

	printf("A read from null %s\n", some_memory);
	sprintf(some_memory, "A write to null\n");
	exit(EXIT_SUCCESS);
}

