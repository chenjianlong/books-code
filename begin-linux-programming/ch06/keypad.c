/*
 * \file keypad.c
 * \brief demo for keypad mode
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-30
 */
/* $Id$ */

#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

#define LOCAL_ESCAPE_KEY 27

int main()
{
	int key;

	initscr();
	crmode();
	keypad(stdscr, TRUE);

	noecho();
	clear();
	mvprintw(5, 5, "Key pad demonstration. Press 'q' to quit");
	move(7, 5);
	refresh();
	key = getch();

	while (key != ERR & key != 'q') {
		move(7, 5);
		clrtoeol();

		if ((key >= 'A' && key <= 'Z') ||
			(key >= 'a' && key <= 'z')) {
			printw("Key was %c", (char)key);
		} else {
			switch (key) {
			case LOCAL_ESCAPE_KEY: 
				printw("%s", "Escape key");
				break;
			case KEY_END:
				printw("%s", "END key");
				break;
			case KEY_BEG:
				printw("%s", "BEG key");
				break;
			case KEY_RIGHT:
				printw("%s", "RIGHT key");
				break;
			case KEY_LEFT:
				printw("%s", "LEFT key");
				break;
			case KEY_UP:
				printw("%s", "UP key");
				break;
			case KEY_DOWN:
				printw("%s", "DOWN key");
				break;
			default:
				printw("Unmatched - %d", key);
				break;
			} /* switch */
		}

		refresh();
		key = getch();
	} /* while */

	endwin();
	exit(EXIT_SUCCESS);
}

