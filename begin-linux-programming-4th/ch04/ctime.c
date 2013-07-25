/*
 * \file ctime.c
 * \brief demo for using ctime
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-05
 */
/* $Id$ */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	time_t timeval;

	(void)time(&timeval);
	printf("The date is: %s", ctime(&timeval));
	exit(0);
}

