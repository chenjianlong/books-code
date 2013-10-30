/*
 * \file fig8.16.c
 * \brief Example of exec functions
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-30
 */
/* $Id$ */

#include "apue.h"
#include <sys/wait.h>

char *env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

int main (void)
{
	pid_t	pid;
	int		size;
	char 	*cwd = path_alloc (&size);
	char	*echoall = "/fig8.17";
	char	*fullpath = NULL;
	
	if (!getcwd (cwd, size)) {
		err_sys ("getcwd error");
	}
	fullpath = malloc (strlen (cwd) + strlen(echoall) + 1);
	strcpy (fullpath, cwd);
	strcpy (fullpath + strlen (cwd), echoall);

	if ((pid = fork ()) < 0) {
		err_sys ("fork error");
	} else if (pid == 0) {
		if (execle (fullpath, "echoall", "myarg1",
					"MY ARG2", (char *)0, env_init) < 0) {
			err_sys ("execle error");
		}
	}

	if (waitpid (pid, NULL, 0) < 0) {
		err_sys ("wait error");
	}

	if ((pid = fork ()) < 0) {
		err_sys ("fork error");
	} else if (pid == 0) {	/* specify filename, inherit environment */
		if (execlp ("fig8.17", "only 1 arg", (char *)0) < 0) {
			err_sys ("execlp error");
		}
	}

	exit (0);
}
