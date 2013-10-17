/*
 * \file ex6.3.c
 * \brief call uname and print all field in utsname
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-18
 */
/* $Id$ */

#include "apue.h"
#include <sys/utsname.h>

int main (void)
{
	struct utsname name;
	if (-1 == uname (&name)) {
		err_sys ("call uname failed");
	}

	printf ("%s %s %s %s %s\n", name.sysname, name.nodename, name.release,
								name.version, name.machine);

	return 0;
}
