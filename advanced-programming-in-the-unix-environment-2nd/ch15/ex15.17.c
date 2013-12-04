/*
 * \file ex15.17.c
 * \brief IPC between parent and child using memory mapped I/O
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-03
 */
/* $Id$ */

#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

#define NLOOPS	1000
#define SIZE	sizeof(long)	/* size of shared memory area */
#define LOCKFILE "./temp.lock"

int fp, fc;

static void tell_wait (void)
{
	if (-1 == (fp = open (LOCKFILE, O_RDWR | O_CREAT, 0600))) {
		err_sys ("open error");
	}

	if (-1 == write (fp, "00", 2)) {
		err_sys ("write error");
	}

	if (-1 == (fc = open (LOCKFILE, O_RDWR | O_CREAT, 0600))) {
		err_sys ("open error");
	}
}

static void wait_parent ()
{
	char buf[1];
	buf[0] = 0;

	while (buf[0] != '1') {
		readw_lock (fc, 1, SEEK_SET, 1);
		lseek (fc, 1, SEEK_SET);
		read (fc, buf, 1);
		if (buf[0] == '1') {
			writew_lock (fc, 1, SEEK_SET, 1);
			lseek (fc, 1, SEEK_SET);
			write (fc, "0", 1);
		}
		un_lock (fc, 1, SEEK_SET, 1);
	}
}

static void tell_parent ()
{
	writew_lock (fc, 0, SEEK_SET, 1);
	lseek (fc, 0, SEEK_SET);
	write (fc, "1", 1);
	un_lock (fc, 0, SEEK_SET, 1);
}

static void wait_child ()
{
	char buf[1];
	buf[0] = 0;

	while (buf[0] != '1') {
		readw_lock (fp, 0, SEEK_SET, 1);
		lseek (fp, 0, SEEK_SET);
		read (fp, buf, 1);
		if (buf[0] == '1') {
			writew_lock (fp, 0, SEEK_SET, 1);
			lseek (fp, 0, SEEK_SET);
			write (fp, "0", 1);
		}
		un_lock (fp, 0, SEEK_SET, 1);
	}
}

static void tell_child ()
{
	writew_lock (fp, 1, SEEK_SET, 1);
	lseek (fp, 1, SEEK_SET);
	write (fp, "1", 1);
	un_lock (fp, 1, SEEK_SET, 1);
}

static int update (long *ptr)
{
	return ((*ptr)++);	/* return value before increment */
}

int main (void)
{
	int		i, counter;
	pid_t	pid;
	void	*area;

	if ((area = mmap (0, SIZE, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED) {
		err_sys ("mmap error");
	}

	tell_wait ();

	if ((pid = fork ()) < 0) {
		err_sys ("fork error");
	} else if (pid > 0) {			/* parent */
		for (i = 0; i < NLOOPS; i += 2) {
			if ((counter = update ((long *)area)) != i) {
				err_quit ("parent: excepted %d, got %d", i, counter);
			}

			tell_child ();
			wait_child ();
		}
	} else {		/* child */
		for (i = 1; i < NLOOPS + 1; i += 2) {
			wait_parent ();

			if ((counter = update ((long *)area)) != i) {
				err_quit ("child: expected %d, got %d", i, counter);
			}

			tell_parent ();
		}
	}

	exit (0);
}
