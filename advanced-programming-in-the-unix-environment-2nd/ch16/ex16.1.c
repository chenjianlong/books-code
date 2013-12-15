/*
 * \file ex16.1.c
 * \brief determine the system's byte ordering
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-15
 */
/* $Id$ */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	unsigned int i = 0x01020304;

	if ((char)i == 0x01) {
		printf ("big-endian byte order\n");
	} else if ((char)i == 0x04) {
		printf ("little-endian byte order\n");
	} else {
		printf ("unknown\n");
	}
	exit (0);
}
