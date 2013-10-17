/*
 * \file ex6.5.c
 * \brief Print the time and date in format similar to date(1)
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-18
 */
/* $Id$ */

#include "apue.h"
#include <time.h>

int main (void)
{
	time_t caltime;
	struct tm *tm;
	char line[MAXLINE];

	if ((caltime = time (NULL)) == -1) {
		err_sys ("time error");
	}
	if ((tm = localtime (&caltime)) == NULL) {
		err_sys ("localtime error");
	}
	if (strftime (line, MAXLINE, "%a %b %d %X %Z %Y\n", tm) == 0) {
		err_sys ("strftime error");
	}
	fputs (line, stdout);
	exit (0);
}
