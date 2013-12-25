/*
 * \file ex17.2.c
 * \brief validate pass file descriptor share the same file table entries
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-25
 */
/* $Id$ */

#include "apue.h"
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

#define TEST_FILE "ex17.2.testfile"

int main (void)
{
	int 	pd[2], fd;
	pid_t 	pid, ppid;
	char 	buf[512];

	TELL_WAIT ();

	if (s_pipe (pd) < 0) {
		err_sys ("s_pipe failed");
	}

	if ((pid = fork ()) < 0) {
		err_sys ("fork failed");
	} else if (pid == 0) {	/* child */
		close (pd[0]);

		ppid = getppid ();
		fd = open (TEST_FILE, O_RDONLY);
		if (fd < 0) {
			send_err (pd[1], errno, "open failed");
			err_sys ("child: open failed");
		}

		if (send_fd (pd[1], fd) < 0) {
			err_sys ("child: send_fd failed");
		}

		TELL_PARENT (ppid);

		if (lseek (fd, 2, SEEK_SET) < 0) {
			err_sys ("child: lseek failed");
		}

		fprintf (stdout, "child: lseek to offset 2\n");

		TELL_PARENT (ppid);
		WAIT_PARENT ();

		if (lseek (fd, 5, SEEK_SET) < 0) {
			err_sys ("child: lseek failed");
		}

		fprintf (stdout, "child: lseek to offset 5\n");
		TELL_PARENT (ppid);
		WAIT_PARENT ();
		fprintf (stdout, "child: exiting...\n");
	} else {	/* parent */
		close (pd[1]);

		WAIT_CHILD ();

		if ((fd = recv_fd (pd[0], write)) < 0) {
			err_sys ("parent: recv_fd failed");
		}

		fprintf (stdout, "parent: received fd: %d\n", fd);

		WAIT_CHILD ();

		if (read (fd, buf, 1) != 1) {
			err_sys ("parent: read failed");
		}
		fprintf (stdout, "parent: read 1 byte: %c\n", buf[0]);

		TELL_CHILD (pid);
		WAIT_CHILD ();

		if (read (fd, buf, 1) != 1) {
			err_sys ("parent: read failed");
		}
		fprintf (stdout, "parent: read 1 byte: %c\n", buf[0]);

		TELL_CHILD (pid);

		fprintf (stdout, "parent: exiting...\n");
	}
	exit (0);
}
