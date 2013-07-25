/*
 * \file checker.c
 * \brief demo valgrind
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-26
 */
/* $Id$ */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *ptr = (char *)malloc(1024);
	char ch;

	/* Uninitialized read */
	ch = ptr[1024];

	/* Write beyond the block */
	ptr[1024] = 0;

	/* Orphan the block */
	ptr = 0;
	exit(0);
}

