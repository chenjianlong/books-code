/*
 * \file fig1.4.c
 * \brief Copy standard input to standard output
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-08-18
 */
/* $Id$ */

#include "apue.h"

#define BUFFSIZE 4096

int main(void)
{
	int n;
	char buf[BUFFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
		if (write(STDOUT_FILENO, buf, n) != n) {
			err_sys("write error");
		}
		if (n < 0) {
			err_sys("read error");
		}
	}
	exit(0);
}

