/*
 * \file ex10.6.c
 * \brief test the TELL_WAIT in Figure 10.24
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-11-14
 */
/* $Id$ */

#include "apue.h"
#include <stdio.h>

#define FILE_NAME "./temp.counter"
static FILE *file = NULL;

void init (void)
{
	TELL_WAIT ();
	file = fopen (FILE_NAME, "w+");
	if (file == NULL) {
		err_quit ("open file failed\n");
	}
	fprintf (file, "%d", 0);
	fflush (file);
}

void increment (pid_t pid)
{
	int count = 0;
	
	if (!file) {
		printf ("file stream invalid.\n");
	}

	rewind (file);
	fscanf (file, "%d", &count);
	++count;
	rewind (file);
	fprintf (file, "%d", count);
	fflush (file);
	printf ("pid: %d increment count to %d\n", pid, count);
}

int main (void)
{
	pid_t	pid = 0, ppid = 0, childpid = 0;
	int		i = 0;

	init ();

	if ((pid = fork ()) < 0) {
		err_sys ("fork error");
	} else if (pid == 0) { /* child block */
		pid = getpid ();
		ppid = getppid ();
		for (i = 0; i < 100; i ++) {
			WAIT_PARENT ();
			increment (pid);
			TELL_PARENT (ppid);
		}
	} else { /* parent block */
		childpid = pid;
		pid = getpid ();
		for (i = 0; i < 100; i ++) {
			increment (pid);
			TELL_CHILD (childpid);
			WAIT_CHILD ();
		}
	}
	exit (0);
}
