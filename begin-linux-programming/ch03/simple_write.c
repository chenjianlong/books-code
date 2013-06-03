/*
 * \file simple_write.c
 * \brief this file is use to demo the write system call
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-03
 */
/* $Id$ */

#include <unistd.h>
#include <stdlib.h>

int main()
{
	if (write(1, "Here is some data\n", 18) != 18) {
		write(2, "A write error has occurred on file descriptor 1\n", 46);
	}

	exit(0);
}

