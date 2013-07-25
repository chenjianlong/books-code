/*
 * \file memory5b.c
 * \brief reading from location zero
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-03
 */
/* $Id$ */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	char z = *(const char *)0;
	printf("I read from location zero\n");

	exit(EXIT_SUCCESS);
}

