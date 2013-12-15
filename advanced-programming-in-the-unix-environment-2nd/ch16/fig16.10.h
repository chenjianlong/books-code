/*!
 * \file fig16.10.h
 * \brief Initialize a socket endpoint for use by a server
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-15
 */
/* $Id$ */

#ifndef FIG16_10_H
#define FIG16_10_H

#include "apue.h"
#include <errno.h>
#include <sys/socket.h>

int initserver (int type, const struct sockaddr *addr, socklen_t alen,
		int qlen)
{
	int fd;
	int err = 0;

	if ((fd = socket (addr->sa_family, type, 0)) < 0) {
		return -1;
	}

	if (bind (fd, addr, alen) < 0) {
		err = errno;
		goto errout;
	}
	if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
		if (listen (fd, qlen) < 0) {
			err = errno;
			goto errout;
		}
	}
	return (fd);

errout:
	close (fd);
	errno = err;
	return -1;
}

#endif /* !FIG16_10_H */
