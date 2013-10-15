/*
 * \file 5.12.c
 * \brief Demonstrate tmpnam and tmpfile functions
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-15
 */
/* $Id$ */

#include "apue.h"

int main (void)
{
	char name[L_tmpnam], line[MAXLINE];
	FILE *fp;

	printf ("%s\n", tmpnam (NULL));

	tmpnam (name);
	printf ("%s\n", name);

	if ((fp = tmpfile ()) == NULL) {
		err_sys ("tmpfile error");
	}
	fputs ("one line of output\n", fp);
	rewind (fp);
	if (fgets (line, sizeof (line), fp) == NULL) {
		err_sys ("fgets error");
	}
	fputs (line, stdout);

	exit (0);
}

