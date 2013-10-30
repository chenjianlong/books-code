/*
 * \file fig8.25.c
 * \brief Print real and effective user IDs
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-30
 */
/* $Id$ */

#include "apue.h"

int main (void)
{
	printf ("real uid = %d, effective uid = %d\n", getuid (), geteuid ());
	exit (0);
}
