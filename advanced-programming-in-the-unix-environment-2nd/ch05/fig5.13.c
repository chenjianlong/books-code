/*
 * \file fig5.13.c
 * \brief Demonstrate tempname function
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-15
 */
/* $Id$ */

#include "apue.h"

int main (int argc, char *argv[])
{
	if (argc != 3) {
		err_quit ("usage: a.out <directory> <prefix>");
	}

	printf ("%s\n", tempnam (argv[1][0] != ' ' ? argv[1] : NULL,
				argv[2][0] != ' ' ? argv[2] : NULL));

	exit (0);
}

