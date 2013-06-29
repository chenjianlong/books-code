/*
 * \file badterm.c
 * \brief demo for badterm
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-29
 */
/* $Id$ */

#include <stdio.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>

int main()
{
	setupterm("unlisted", fileno(stdout), (int*)0);
	printf("Done.\n");
	exit(0);
}

