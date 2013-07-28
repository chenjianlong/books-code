/*
 * \file pexec.c
 * \brief demo for execlp
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-27
 */
/* $Id$ */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Running ps with execlp\n");
	execlp("ps", "ps", "ax", 0);
	printf("Done.\n");
	exit(0);
}

