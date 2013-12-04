/*
 * \file ex15.15.c
 * \brief IPC between parent and child using XSI shared memory
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-03
 */
/* $Id$ */

#include "apue.h"
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define DEFMODE 0600
#define NLOOPS	1000
#define SIZE	sizeof(long)	/* size of shared memory area */

static int update (long *ptr)
{
	return ((*ptr)++);	/* return value before increment */
}

int main (void)
{
	int		i, counter, shmid, status;
	pid_t	pid;
	void	*area;

	if (-1 == (shmid = shmget (IPC_PRIVATE, sizeof (long),
					DEFMODE | IPC_CREAT | IPC_EXCL))) {
		err_sys ("shmget error");
	}
	if ((void *)-1 == (area = shmat (shmid, 0, 0))) {
		err_sys ("shmat error");
	}

	TELL_WAIT ();

	if ((pid = fork ()) < 0) {
		err_sys ("fork error");
	} else if (pid > 0) {			/* parent */
		for (i = 0; i < NLOOPS; i += 2) {
			if ((counter = update ((long *)area)) != i) {
				err_quit ("parent: excepted %d, got %d", i, counter);
			}

			TELL_CHILD (pid);
			WAIT_CHILD ();
		}

		if (waitpid (pid, &status, 0) < 0) {
			err_sys ("waitpid error");
		}

		if (-1 == shmdt (area)) {
			err_sys ("shmdt error");
		}

		if (-1 == shmctl (shmid, IPC_RMID, 0)) {
			err_sys ("shmctl error");
		}
	} else {		/* child */
		for (i = 1; i < NLOOPS + 1; i += 2) {
			WAIT_PARENT ();

			if ((counter = update ((long *)area)) != i) {
				err_quit ("child: expected %d, got %d", i, counter);
			}

			TELL_PARENT (getppid ());
		}

		if (-1 == shmdt (area)) {
			err_sys ("shmdt error");
		}
	}

	exit (0);
}
