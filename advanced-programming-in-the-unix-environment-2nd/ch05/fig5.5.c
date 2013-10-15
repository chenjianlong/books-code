/*
 * \file fig5.5.c
 * \brief Copy standard input to standard output using fgets and fputs
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-15
 */
/* $Id$ */

#include "apue.h"

int main (void)
{
	char buf[MAXLINE];

	while (fgets (buf, MAXLINE, stdin) != NULL) {
		if (fputs (buf, stdout) == EOF) {
			err_sys ("output error");
		}
	}

	if (ferror (stdin)) {
		err_sys ("input error");
	}

	exit (0);
}

