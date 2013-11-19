/*
 * \file ex13.1.c
 * \brief chroot before openlog
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-11-19
 */
/* $Id$ */

#include "apue.h"
#include <syslog.h>

int main (int argc, char *argv[])
{
	/*if (chdir ("/usr/local") < 0) {
		err_sys ("chdir failed");
	}*/

	openlog (argv[0], LOG_CONS, LOG_LOCAL0);
	syslog (LOG_ERR, "test log by ex13.1");
	while (1) {
		sleep (3);
	}
	exit (1);
}

