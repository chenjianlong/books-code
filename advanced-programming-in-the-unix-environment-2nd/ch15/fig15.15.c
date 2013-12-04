/*
 * \file fig15.15.c
 * \brief Invoker uppercase/lowercase filter to read commands
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-03
 */
/* $Id$ */

#include "apue.h"
#include <sys/wait.h>

int main (void)
{
	char	line[MAXLINE];
	FILE	*fpin;

	if ((fpin = popen ("./fig15.14", "r")) == NULL) {
		err_sys ("popen error");
	}
	for (;;) {
		fputs ("prompt> ", stdout);
		fflush (stdout);
		if (fgets (line, MAXLINE, fpin) == NULL) {	/* read from pipe */
			break;
		}
		if (fputs (line, stdout) == EOF) {
			err_sys ("fputs error to pipe");
		}
	}
	if (pclose (fpin) == -1) {
		err_sys ("pclose error");
	}
	putchar ('\n');
	exit (0);
}
