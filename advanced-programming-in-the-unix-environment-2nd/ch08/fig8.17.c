/*
 * \file fig8.17.c
 * \brief Echo all command-line arguments and all environment strings
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-30
 */
/* $Id$ */

#include "apue.h"

int main (int argc, char *argv[])
{
	int			i;
	char		**ptr;
	extern char **environ;

	for (i = 0; i < argc; i++) {		/* echo all command-line args */
		printf ("argv[%d]: %s\n", i, argv[i]);
	}

	for (ptr = environ; *ptr != 0; ptr++) {	/* and all env strings */
		printf ("%s\n", *ptr);
	}

	exit (0);
}
