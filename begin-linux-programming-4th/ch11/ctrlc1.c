/*
 * \file ctrlc1.c
 * \brief demo for catch signal
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-28
 */
/* $Id$ */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig)
{
	printf("OUCH! - I got signal %d\n", sig);
	signal(SIGINT, SIG_DFL);
}

int main()
{
	signal(SIGINT, ouch);

	while (1) {
		printf("Hello World!\n");
		sleep(1);
	}
}

