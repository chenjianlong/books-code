/*
 * \file fig1.5.c
 * \brief Copy standard input to standard output, using standard I/O
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-08-18
 */
/* $Id$ */

#include "apue.h"

int main(void)
{
	int c;
	while ((c = getc(stdin)) != EOF) {
		if (putc(c, stdout) == EOF) {
			err_sys("output error");
		}
	}

	if (ferror(stdin)) {
		err_sys("input error");
	}
	exit(0);
}

