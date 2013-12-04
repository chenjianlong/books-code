/*
 * \file fig15.14.c
 * \brief Filter to convert uppercase characters to lowercase
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-03
 */
/* $Id$ */

#include "apue.h"
#include <ctype.h>

int main (void)
{
	int		c;

	while ((c = getchar ()) != EOF) {
		if (isupper (c)) {
			c = tolower (c);
		}
		if (putchar (c) == EOF) {
			err_sys ("output error");
		}
		if (c == '\n') {
			fflush (stdout);
		}
	}
	exit (0);
}
