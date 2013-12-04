/*
 * \file fig15.5.c
 * \brief Send data from parent to child over a pipe
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-03
 */
/* $Id$ */

#include "apue.h"

int main (void)
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	line[MAXLINE];

	if (pipe (fd) < 0) {
		err_sys ("pipe error");
	}
	if ((pid = fork ()) < 0) {
		err_sys ("fork error");
	} else if (pid > 0) {	/* parent */
		close (fd[0]);
		write (fd[1], "hello world\n", 12);
	} else {				/* child */
		close (fd[1]);
		n = read (fd[0], line, MAXLINE);
		write (STDOUT_FILENO, line, n);
	}
	exit (0);
}
