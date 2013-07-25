/*
 * \file screen1.c
 * \brief demo for simple curses use
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-30
 */
/* $Id$ */

#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main()
{
	initscr();

	move(5, 15);
	printw("%s", "Hello World");
	refresh();

	sleep(2);

	endwin();
	exit(EXIT_SUCCESS);
}

