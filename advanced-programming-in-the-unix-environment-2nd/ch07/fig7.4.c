/*
 * \file fig7.4.c
 * \brief Echo all command-line arguments to standard output
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-24
 */
/* $Id$ */

#include "apue.h"

int main (int argc, char *argv[])
{
	int i;

	for (i = 0; i < argc; i++) {
		printf ("argv[%d]: %s\n", i, argv[i]);
	}
	exit (0);
}
