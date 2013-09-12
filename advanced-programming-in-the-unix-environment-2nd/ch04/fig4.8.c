/*
 * \file fig4.8.c
 * \brief Example of access function
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-09-12
 */
/* $Id$ */

#include "apue.h"
#include <fcntl.h>

int main (int argc, char *argv[])
{
	if (argc != 2) {
		err_quit ("usage: fig4.8 <pathname>");
	}
	if (access (argv[1], R_OK) < 0) {
		err_ret ("access error for %s", argv[1]);
	} else {
		printf ("read access OK\n");
	}
	if (open (argv[1], O_RDONLY) < 0) {
		err_ret ("open error for %s", argv[1]);
	} else {
		printf ("open for reading OK\n");
	}
	exit (0);
}

