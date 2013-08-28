/*
 * \file fig3.1.c
 * \brief Test whether standard input is capable of seeking
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-08-26
 */
/* $Id$ */

#include "apue.h"

int main(void)
{
	if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) {
		printf("cannot seek\n");
	} else {
		printf("seek OK\n");
	}
	exit(0);
}

