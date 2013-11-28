/*
 * \file ex14.6.c
 * \brief Implement sleep_us with select
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-11-28
 */
/* $Id$ */

#include "apue.h"
#include <sys/select.h>

void sleep_us (unsigned int nusecs)
{
	struct timeval tval;

	tval.tv_sec = nusecs / 1000000;
	tval.tv_usec = nusecs % 1000000;
	select (0, NULL, NULL, NULL, &tval);
}

int main (void)
{
	printf ("begin to sleep_us 3000000 microseconds\n");
	sleep_us (3000000);
	printf ("after sleep_us 3000000 microseconds\n");
	return 0;
}
