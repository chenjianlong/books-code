/*!
 * \file fig17.13.h
 * \brief Socket version of the s_pipe function
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-23
 */
/* $Id$ */

#ifndef FIG17_13_H
#define FIG17_13_H

#include "apue.h"
#include <sys/socket.h>

/*
 * Returns a full-duplex "stream" pipe (a UNIX domain socket)
 * with the two file descriptors returned in fd[0] and fd[1].
 */
int s_pipe (int fd[2])
{
	return socketpair (AF_UNIX, SOCK_STREAM, 0, fd);
}

#endif /* !FIG17_13_H */
