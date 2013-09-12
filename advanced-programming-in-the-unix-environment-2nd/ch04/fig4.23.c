/*
 * \file fig4.23.c
 * \brief Example of chdir function
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-09-12
 */
/* $Id$ */

#include "apue.h"

int main (void)
{
	if (chdir ("/tmp") < 0) {
		err_sys ("chdir failed");
	}
	printf ("chdir to /tmp succeeded\n");
	exit (0);
}

