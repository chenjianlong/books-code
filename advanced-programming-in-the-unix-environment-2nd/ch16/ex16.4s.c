/*
 * \file ex16.4s.c
 * \brief Server program illustrating writing number of processes to socket
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-15
 */
/* $Id$ */

#include "apue.h"
#include "fig16.20.h"
#include <errno.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>

#define QLEN 10

void serve (int sockfd)
{
	int		clfd, status;
	pid_t	pid;

	for (;;) {
		clfd = accept (sockfd, NULL, NULL);
		if (clfd < 0) {
			syslog (LOG_ERR, "ruptimed: accept error: %s",
					strerror (errno));
			exit (1);
		}
		if ((pid = fork ()) < 0) {
			syslog (LOG_ERR, "ruptimed: fork error: %s",
					strerror (errno));
			exit (1);
		} else if (pid == 0) {	/* child */
			/*
			 * The parent called daemonize (Figure 13.1), so
			 * STDIN_FILENO, STDOUT_FILENO, and STDERR_FILENO
			 * are already open to /dev/null. Thus, the call to
			 * close doesn't need to be protected by checks that
			 * clfd isn't already equal to one of these values.
			 */
			if (dup2 (clfd, STDOUT_FILENO) != STDOUT_FILENO ||
					dup2 (clfd, STDERR_FILENO) != STDERR_FILENO) {
				syslog (LOG_ERR, "ruptimd: unexpected error");
				exit (1);
			}
			close (clfd);
			execlp ("/bin/sh", "sh", "-c", "ps aux | wc -l", (char *)0);
			syslog (LOG_ERR, "ruptimed: unexpected return from exec: %s",
					strerror (errno));
		} else { /* parent */
			close (clfd);
			waitpid (pid, &status, 0);
		}
	}
}

int main (int argc, char *argv[])
{
	struct sockaddr_in addr;
	int				sockfd;

	if (argc != 2) {
		err_quit ("usage: %s <port>", argv[0]);
	}
	daemonize ("ruptimed");
	memset (&addr, '\0', sizeof (addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl (INADDR_ANY);
	addr.sin_port = htons (atoi (argv[1]));
	if ((sockfd = initserver (SOCK_STREAM, (const struct sockaddr*)&addr,
					sizeof (addr), QLEN)) >= 0) {
		serve (sockfd);
		exit (0);
	}
	exit (1);
}
