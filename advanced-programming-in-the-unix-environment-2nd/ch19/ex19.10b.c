/*
 * \file ex19.10b.c
 * \brief caught signal
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2014-01-07
 */
/* $Id$ */

#include "apue.h"
#include <fcntl.h>

static int log_fd;

static void sig_term (int signo)
{
	char msg[] = "sig term caught\n";
	write (log_fd, msg, sizeof (msg));
}

int main (void)
{
	if ((log_fd = open ("./ex19.10b.log", O_RDWR | O_CREAT)) < 0) {
		err_sys ("open failed");
	}
	if (signal_intr (SIGTERM, sig_term) == SIG_ERR) {
		err_sys ("signal_intr error for SIGTERM");
	}

	while (1) {
		sleep (1);
	}
}

