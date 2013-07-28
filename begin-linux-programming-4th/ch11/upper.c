/*
 * \file upper.c
 * \brief convert input to upper
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-27
 */
/* $Id$ */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
	int ch;
	while ((ch = getchar()) != EOF) {
		putchar(toupper(ch));
	}
	exit(0);
}

