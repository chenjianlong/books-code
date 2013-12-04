/*
 * \file ex15.16.c
 * \brief IPC between parent and child using memory mapped I/O
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-03
 */
/* $Id$ */

#include "apue.h"
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "semun.h"

#define DEFMODE 0600
#define NLOOPS	1000
#define SIZE	sizeof(long)	/* size of shared memory area */

int semid;

static void tell_wait ()
{
	union semun sem_union;
	sem_union.val = 0;

	if (-1 == (semid = semget (IPC_PRIVATE, 2,
					IPC_CREAT | IPC_EXCL | DEFMODE))) {
		err_sys ("semget error");
	}

	if (-1 == semctl (semid, 0, SETVAL, sem_union) ||
			-1 == semctl (semid, 1, SETVAL, sem_union)) {
		err_sys ("semctl error");
	}
}

static void del_sem ()
{
	union semun sem_union;
	sem_union.val = 0;
	
	if (-1 == semctl (semid, 0, IPC_RMID, sem_union)) {
		err_sys ("semctl IPC_RMID error");
	}
}

static void wait_parent ()
{
	struct sembuf sem_b;

	sem_b.sem_num = 1;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	if (-1 == semop (semid, &sem_b, 1)) {
		err_sys ("semop error");
	}
}

static void tell_parent ()
{
	struct sembuf sem_b;

	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	if (-1 == semop (semid, &sem_b, 1)) {
		err_sys ("semop error");
	}
}

static void wait_child ()
{
	struct sembuf sem_b;

	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	if (-1 == semop (semid, &sem_b, 1)) {
		err_sys ("semop error");
	}
}

static void tell_child ()
{
	struct sembuf sem_b;

	sem_b.sem_num = 1;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	if (-1 == semop (semid, &sem_b, 1)) {
		err_sys ("semop error");
	}
}

static int update (long *ptr)
{
	return ((*ptr)++);	/* return value before increment */
}

int main (void)
{
	int		i, counter, status;
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

		if (-1 == waitpid (pid, &status, 0)) {
			err_sys ("waitpid error");
		}

		del_sem ();
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
