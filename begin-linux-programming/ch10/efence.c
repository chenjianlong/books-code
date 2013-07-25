/*
 * \file efence.c
 * \brief demo for efence
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-26
 */
/* $Id$ */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *ptr = (char *)malloc(1024);
	ptr[0] = 0;

	/* Now write beyond the block */
	ptr[1024] = 0;
	exit(0);
}

