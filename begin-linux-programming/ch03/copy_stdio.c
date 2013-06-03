/*
 * \file copy_stdio.c
 * \brief copy file use stdio
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-06-03
 */
/* $Id$ */

#include <stdio.h> 
#include <stdlib.h>

int main() 
{
	int c;
	FILE *in, *out;
	in = fopen("file.in", "r");
	out = fopen("file.out", "w");

	while((c = fgetc(in)) != EOF) {
		fputc(c,out);
	}

	exit(0); 
}

