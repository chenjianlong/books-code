/*
 * \file fig18.18.c
 * \brief Call the get_pass function
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-29
 */
/* $Id$ */

#include "apue.h"
#include "fig18.17.h"

int main (void)
{
	char	*ptr;

	if ((ptr = getpass ("Enter password:")) == NULL) {
		err_sys ("get_pass error");
	}
	printf ("password: %s\n", ptr);

	/* now use password (probably encrypt it) ... */

	while (*ptr != 0) {
		*ptr++ = 0;	/* zero it out when we're done with it */
	}
	exit (0);
}
