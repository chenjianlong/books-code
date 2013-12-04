/*
 * \file ex15.3.c
 * \brief popen an nonexistent command
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-03
 */
/* $Id$ */

#include "apue.h"

int main (void)
{
	FILE *fp = popen ("/bin/noexistent", "r");

	if (fp == NULL) {
		err_sys ("popen failed");
	}

	int status = pclose (fp);
	pr_exit (status);
	exit (0);
}
