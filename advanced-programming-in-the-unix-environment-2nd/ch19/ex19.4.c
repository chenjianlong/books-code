/*
 * \file ex19.4.c
 * \brief The loop function use select
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2014-01-05
 */
/* $Id$ */

#include "apue.h"
/* According to POSIX.1-2001 */
#include <sys/select.h>
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


#define BUFFSIZE 512

void loop (int ptym, int ignoreeof)
{
	int		nread, maxfd, n;
	char	buf[BUFFSIZE];
	fd_set  rset, wset, vrset, vwset;

	FD_ZERO (&rset);
	FD_ZERO (&wset);
	FD_SET (STDIN_FILENO, &rset);
	FD_SET (STDOUT_FILENO, &wset);

	maxfd = STDOUT_FILENO > STDIN_FILENO ? STDOUT_FILENO : STDIN_FILENO;

	for (;;) {
		vrset = rset;
		vwset = wset;
		if ((n = select (maxfd + 1, &vrset, &vwset, NULL, NULL)) < 0) {
			err_sys ("select error");
		}
		if (FD_ISSET (STDIN_FILENO, &vrset)) {
			if ((nread = read (STDIN_FILENO, buf, BUFFSIZE)) < 0) {
				err_sys ("read error from stdin");
			} else if (nread == 0) {
				FD_CLR (STDIN_FILENO, &rset);
				if (ignoreeof == 0) {
					exit (0);
				}
			}
			if (writen (ptym, buf, nread) != nread) {
				err_sys ("writen error to master pty");
			}
		}

		if (FD_ISSET (STDOUT_FILENO, &vwset)) {
			if ((nread = read (ptym, buf, BUFFSIZE)) <= 0) {
				exit (0); /* signal caught, error, or EOF */
			}
			if (writen (STDOUT_FILENO, buf, nread) != nread) {
				err_sys ("writen error to stdout");
			}
		}
	} /* for (;;) */
}
