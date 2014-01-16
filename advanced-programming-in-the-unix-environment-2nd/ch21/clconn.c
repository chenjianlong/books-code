/*!
 * \file clconn.c (copy from fig16.9.h)
 * \brief Connect with retry
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-15
 */
/* $Id$ */


#include "apue.h"
#include <sys/socket.h>

#define MAXSLEEP 128

int connect_retry (int sockfd, const struct sockaddr *addr, socklen_t alen)
{
	int nsec;

	/*
	 * Try to connect with exponential backoff
	 */
	for (nsec = 1; nsec <= MAXSLEEP; nsec <<= 1) {
		if (connect (sockfd, addr, alen) == 0) {
			/*
			 * Connection accepted
			 */
			return 0;
		}

		/*
		 * Delay before trying again.
		 */
		if (nsec <= MAXSLEEP / 2) {
			sleep (nsec);
		}
	}
	return -1;
}
