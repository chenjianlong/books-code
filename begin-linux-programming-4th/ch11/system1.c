/*
 * \file system1.c
 * \brief demo for system
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-27
 */
/* $Id$ */

#include <stdlib.h>
#include <stdio.h>

int main()
{
	printf("Running ps with system\n");
	system("ps ax");
	printf("Done.\n");
	exit(0);
}

