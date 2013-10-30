/*
 * \file ex8.2.c
 * \brief After vfork return from sub-function
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-30
 */
/* $Id$ */

#include "apue.h"

static void f1 (void)
{
	pid_t pid;

	if ((pid = vfork ()) < 0) {
		err_sys ("vfork error");
	}
}

static void f2 (void)
{
	char buf[1000];			/* automatic variables */
	int	 i;

	for (i = 0; i < sizeof (buf); i++) {
		buf[i] = 0;
	}
}

int main (void)
{
	f1 ();
	f2 ();
	_exit (0);
}
