/*
 * \file fig10.26.c
 * \brief Using system to invoke the ed editor
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-11-14
 */
/* $Id$ */

#include "apue.h"

static void sig_int (int signo)
{
	printf("caught SIGINT\n");
}

static void sig_chld (int signo)
{
	printf("caught SIGCHLD\n");
}

int main(void)
{
	if (signal(SIGINT, sig_int) == SIG_ERR) {
		err_sys("signal(SIGINT) error");
	}
	if (signal(SIGCHLD, sig_chld) == SIG_ERR) {
		err_sys("signal(SIGCHLD) error");
	}
	if (system("/bin/ed") < 0) {
		err_sys("system() error");
	}
	exit(0);
}

