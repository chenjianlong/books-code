/*
 * \file ex18.1.c
 * \brief set tty_raw and terminates
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-29
 */
/* $Id$ */

#include "apue.h"

int main (void)
{
	if (tty_raw (STDIN_FILENO) < 0) {
		err_sys ("tty_raw error");
	}
	exit (0);
}
