/*
 * \file showenv.c
 * \brief demo for show environ
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-05
 */
/* $Id$ */

#include <stdlib.h>
#include <stdio.h>

extern char **environ;

int main()
{
	char **env = environ;

	while (*env) {
		printf("%s\n", *env);
		env++;
	}

	exit(0);
}

