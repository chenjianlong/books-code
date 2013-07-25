/*
 * \file syslog.c
 * \brief demo for syslog
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-07
 */
/* $Id$ */

#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *f;

	f = fopen("not_here", "r");
	if (!f) {
		syslog(LOG_ERR|LOG_USER, "oops - %m\n");
	}
	exit(0);
}

