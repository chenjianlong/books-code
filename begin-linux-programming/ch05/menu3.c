/*
 * \file menu3.c
 * \brief demo of menu3
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-18
 */
/* $Id$ */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *menu[] = {
	"a - add new record",
	"d - delete record",
	"q - quit",
	NULL
};

int getchoice(char *greet, char *choices[], FILE *in, FILE *out);

int main()
{
	int choice = 0;
	FILE *input = NULL;
	FILE *output = NULL;

	if (!isatty(fileno(stdout))) {
		fprintf(stderr, "You are not a terminal, OK.\n");
	}
	input = fopen("/dev/tty", "r");
	output = fopen("/dev/tty", "w");
	if (!input || !output) {
		fprintf(stderr, "Unable to open /dev/tty\n");
		exit(1);
	}
	do {
		choice = getchoice("Please select an action", menu, input, output);
		printf("You have chosen: %c\n", choice);
	} while(choice != 'q');
	exit(0);
}

int getchoice(char *greet, char *choices[], FILE *in, FILE *out)
{
	int chosen = 0;
	int selected;
	char **option;

	do {
		fprintf(out, "Choice: %s\n", greet);
		option = choices;
		while (*option) {
			fprintf(out, "%s\n", *option);
			option++;
		}
		do {
			selected = fgetc(in);
		} while(selected == '\n');
		option = choices;
		while (*option) {
			if (selected == (*option)[0]) {
				chosen = 1;
				break;
			}
			option++;
		}
		if (!chosen) {
			fprintf(out, "Incorrect choice, select again\n");
		}
	} while(!chosen);
	return selected;
}

