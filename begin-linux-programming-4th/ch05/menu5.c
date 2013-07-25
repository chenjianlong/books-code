/*
 * \file menu4.c
 * \brief demo of menu5
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-29
 */
/* $Id$ */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <term.h>
#include <curses.h>

static FILE *output_stream = (FILE *)0;

char *menu[] = {
	"a - add new record",
	"d - delete record",
	"q - quit",
	NULL
};

int getchoice(char *greet, char *choices[], FILE *in, FILE *out);
int char_to_terminal(int char_to_write);

int main()
{
	int choice = 0;
	FILE *input = NULL;
	FILE *output = NULL;
	struct termios initial_settings, new_settings;

	if (!isatty(fileno(stdout))) {
		fprintf(stderr, "You are not a terminal, OK.\n");
	}
	input = fopen("/dev/tty", "r");
	output = fopen("/dev/tty", "w");
	if (!input || !output) {
		fprintf(stderr, "Unable to open /dev/tty\n");
		exit(1);
	}

	/* Set terminal */
	tcgetattr(fileno(input), &initial_settings);
	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	if (tcsetattr(fileno(input), TCSANOW, &new_settings) != 0) {
		fprintf(stderr, "could not set attributes\n");
	}

	do {
		choice = getchoice("Please select an action", menu, input, output);
		printf("You have chosen: %c\n", choice);
		sleep(1);
	} while(choice != 'q');

	/* Restore terminal */
	tcsetattr(fileno(input), TCSANOW, &initial_settings);

	exit(0);
}

int getchoice(char *greet, char *choices[], FILE *in, FILE *out)
{
	int chosen = 0;
	int selected;
	int screenrow, screencol = 10;

	char **option;
	char *cursor, *clear;

	output_stream = out;

	setupterm(NULL, fileno(out), (int *)0);
	cursor = tigetstr("cup");
	clear = tigetstr("clear");

	screenrow = 4;
	tputs(clear, 1, char_to_terminal);
	tputs(tparm(cursor, screenrow, screencol), 1, char_to_terminal);
	fprintf(out, "Choice: %s", greet);
	screenrow += 2;
	option = choices;
	while (*option) {
		tputs(tparm(cursor, screenrow, screencol), 1, char_to_terminal);
		fprintf(out, "%s", *option);
		screenrow++;
		option++;
	}
	fprintf(out, "\n");

	do {
		fflush(out);
		selected = fgetc(in);
		option = choices;
		while(*option) {
			if (selected == (*option)[0]) {
				chosen = 1;
				break;
			}
			option++;
		}
		if (!chosen) {
			tputs(tparm(cursor, screenrow, screencol), 1, char_to_terminal);
			fprintf(out, "Incorrect choice, select again\n");
		}
	} while(!chosen);
	tputs(clear, 1, char_to_terminal);
	return selected;
}

int char_to_terminal(int char_to_write)
{
	if (output_stream) {
		putc(char_to_write, output_stream);
	}
	return 0;
}

