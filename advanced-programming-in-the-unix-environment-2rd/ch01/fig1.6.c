/*
 * \file fig1.6.c
 * \brief Print the process ID
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-08-18
 */
/* $Id$ */

#include "apue.h"

int main(void)
{
	printf("hello world from process ID %d\n", getpid());
	exit(0);
}


