/*
 * \file password.c
 * \brief disable echo to wait use press the password
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-29
 */
/* $Id$ */

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

#define PASSWORD_LEN 8

int main()
{
	struct termios initial_settings, new_settings;
	char password[PASSWORD_LEN + 1];

	tcgetattr(fileno(stdin), &initial_settings);

	new_settings = initial_settings;
	new_settings.c_lflag &= ~ECHO;

	printf("Enter password: ");

	if (tcsetattr(fileno(stdin), TCSAFLUSH, &new_settings) != 0) {
		fprintf(stderr, "Could not set attributes\n");
	} else {
		fgets(password, PASSWORD_LEN, stdin);
		tcsetattr(fileno(stdin), TCSANOW, &initial_settings);
		fprintf(stdout, "\nYou entered %s\n", password);
	}
	exit(0);
}

