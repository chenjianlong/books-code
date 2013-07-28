/*
 * \file ctrlc2.c
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
}

int main()
{
	struct sigaction act;

	act.sa_handler = ouch;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	/* act.sa_flags = SA_RESETHAND; */

	sigaction(SIGINT, &act, 0);

	while (1) {
		printf("Hello World!\n");
		sleep(1);
	}
}

