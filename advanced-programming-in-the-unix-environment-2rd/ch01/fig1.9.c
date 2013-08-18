/*
 * \file fig1.9.c
 * \brief Print user ID and group ID
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-08-18
 */
/* $Id$ */

#include "apue.h"

int main(void)
{
	printf("uid = %d, gid = %d\n", getuid(), getgid());
	exit(0);
}

