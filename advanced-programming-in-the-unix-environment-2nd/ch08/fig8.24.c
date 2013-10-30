/*
 * \file fig8.24.c
 * \brief Execute the command-line argument using system
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-30
 */
/* $Id$ */

#include "apue.h"

int main (int argc, char *argv[])
{
	int		status;

	if (argc < 2) {
		err_quit ("command-line argument required");
	}

	if ((status = system (argv[1])) < 0) {
		err_sys ("system () error");
	}
	pr_exit (status);

	exit (0);
}
