/*
 * \file fig8.20.c
 * \brief A program that execs an interpreter file
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-30
 */
/* $Id$ */

#include "apue.h"
#include <sys/wait.h>

int main (void)
{
	pid_t	pid;
	int		size;
	char 	*cwd = path_alloc (&size);
	char	*echoall = "/testinterp";
	char	*fullpath = NULL;
	
	if (!getcwd (cwd, size)) {
		err_sys ("getcwd error");
	}
	fullpath = malloc (strlen (cwd) + strlen(echoall) + 1);
	strcpy (fullpath, cwd);
	strcpy (fullpath + strlen (cwd), echoall);

	if ((pid = fork ()) < 0) {
		err_sys ("fork error");
	} else if (pid == 0) {			/* child */
		if (execl (fullpath, "testinterp", "myarg1", "MY_ARG2",
					(char *)0) < 0) {
			err_sys ("execl error");
		}
	}

	if (waitpid (pid, NULL, 0) < 0) { /* parent */
		err_sys ("waitpid error");
	}
	exit (0);
}
