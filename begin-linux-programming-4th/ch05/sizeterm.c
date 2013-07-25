/*
 * \file sizeterm.c
 * \brief find out the size of terminal
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
	int nrows, ncolumns;
	char *cup;

	setupterm(NULL, fileno(stdout), (int*)0);
	nrows = tigetnum("lines");
	ncolumns = tigetnum("cols");
	printf("This terminal has %d columns and %d rows\n", ncolumns, nrows);
	exit(0);
}

