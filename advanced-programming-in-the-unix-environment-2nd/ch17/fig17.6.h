/*!
 * \file fig17.6.h
 * \brief STREAMS version of the s_pipe function
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-23
 */
/* $Id$ */

#ifndef FIG17_6_H
#define FIG17_6_H

#include "apue.h"

/*
 * Returns a STREAMS-based pipe, with the two file descriptors
 * returned in fd[0] and fd[1].
 */
int s_pipe (int fd[2])
{
	return pipe (fd);
}

#endif /* !FIG17_6_H */


