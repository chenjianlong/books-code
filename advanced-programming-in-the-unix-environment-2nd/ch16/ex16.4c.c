/*
 * \file ex16.4c.c
 * \brief Client command to get number of processes from server
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-15
 */
/* $Id$ */

#include "apue.h"
#include "fig16.9.h"
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXADDRLEN 256
#define BUFLEN 128

void print_num_of_processes (int sockfd)
{
	int		n;
	char	buf[BUFLEN];

	while ((n = recv (sockfd, buf, BUFLEN, 0)) > 0) {
		write (STDOUT_FILENO, buf, n);
	}
	if (n < 0) {
		err_sys ("recv error");
	}
}

int main (int argc, char *argv[])
{
	struct sockaddr_in addr;
	int				sockfd, err;

	if (argc != 2) {
		err_quit ("usage: %s <port>", argv[0]);
	}

	memset (&addr, '\0', sizeof (addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl (INADDR_ANY);
	addr.sin_port = htons (atoi (argv[1]));
	if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
		err = errno;
	} else {
		if (connect_retry (sockfd, (const struct sockaddr *)&addr,
					sizeof (addr)) < 0) {
			err = errno;
		} else {
			print_num_of_processes (sockfd);
			exit (0);
		}
	}
	fprintf (stderr, "can't connect to %s: %s\n", argv[1], strerror (err));
	exit (0);
}
