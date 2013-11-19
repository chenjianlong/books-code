/*
 * \file ex13.3.c
 * \brief get login name after daemonize
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-11-19
 */
/* $Id$ */

#include "apue.h"

int main (void)
{
	FILE *fp = NULL;
	char *p = NULL;

	daemonize ("getlog");
	p = getlogin ();
	fp = fopen ("/tmp/getlog.out", "w");
	if (fp != NULL) {
		if (p == NULL) {
			fprintf (fp, "no login name\n");
		} else {
			fprintf (fp, "login name: %s\n", p);
		}
	}
	exit (0);
}
