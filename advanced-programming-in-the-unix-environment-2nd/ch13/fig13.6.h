/*!
 * \file fig13.6.h
 * \brief Ensure that only one copy of a daemon is running
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-11-19
 */
/* $Id$ */

#ifndef FIG13_6_H
#define FIG13_6_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

/* copy from Figure 14.9 */
int lockfile (int fd)
{
	struct flock fl;

	fl.l_type = F_WRLCK;
	fl.l_start = 0;
	fl.l_whence = SEEK_SET;
	fl.l_len = 0;
	return (fcntl (fd, F_SETLK, &fl));
}

int already_running (void)
{
	int		fd;
	char	buf[16];

	fd = open (LOCKFILE, O_RDWR | O_CREAT, LOCKMODE);
	if (fd < 0) {
		syslog (LOG_ERR, "can't open %s: %s", LOCKFILE, strerror (errno));
		exit (1);
	}
	if (lockfile (fd) < 0) {
		if (errno == EACCES || errno == EAGAIN) {
			close (fd);
			return (1);
		}
		syslog (LOG_ERR, "can't lock %s: %s", LOCKFILE, strerror (errno));
		exit (1);
	}
	ftruncate (fd, 0);
	sprintf (buf, "%ld", (long)getpid ());
	write (fd, buf, strlen (buf) + 1);
	return (0);
}

#endif /* !FIG13_6_H */
