/*
 * \file fig15.19.c
 * \brief Filter to add two numbers, using standard I/O
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-03
 */
/* $Id$ */

#include "apue.h"

int main (void)
{
	int		int1, int2;
	char	line[MAXLINE];

	if (setvbuf (stdin, NULL, _IOLBF, 0) != 0) {
		err_sys ("setvbuf error");
	}
	if (setvbuf (stdout, NULL, _IOLBF, 0) != 0) {
		err_sys ("setvbuf error");
	}
	while (fgets (line, MAXLINE, stdin) != NULL) {
		if (sscanf (line, "%d%d", &int1, &int2) == 2) {
			if (printf ("%d\n", int1 + int2) == EOF) {
				err_sys ("printf error");
			}
		} else {
			if (printf ("invalid args\n") == EOF) {
				err_sys ("printf error");
			}
		}
	}
	exit (0);
}
