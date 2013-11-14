/*
 * \file fig10.5.c
 * \brief Call a nonreentrant function from a signal handler
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-11-13
 */
/* $Id$ */

#include "apue.h"
#include <pwd.h>

static void my_alarm (int signo)
{
	struct passwd *rootptr;

	printf ("in signal handler\n");
	if ((rootptr = getpwnam ("root")) == NULL) {
		err_sys ("getpwnam (root) error");
	}
	alarm (1);
}

int main (void)
{
	struct passwd *ptr;

	signal (SIGALRM, my_alarm);
	alarm (1);
	for ( ; ; ) {
		if ((ptr = getpwnam ("cjl")) == NULL) {
			err_sys ("getpwnam error");
		}
		if (strcmp (ptr->pw_name, "cjl") != 0) {
			printf ("return value corrupted!, pw_name = %s\n",
					ptr->pw_name);
		}
	}
	exit (0);
}
