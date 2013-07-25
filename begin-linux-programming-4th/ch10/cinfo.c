/*
 * \file cinfo.c
 * \brief print information about its compilation date and time if debugging is enabled
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-23
 */
/* $Id$ */


#include <stdio.h>
#include <stdlib.h>
int main()
{
#ifdef DEBUG
	printf("Compiled: " __DATE__ " at " __TIME__ "\n");
	printf("This is line %d of file %s\n", __LINE__, __FILE__);
#endif
	printf("hello world\n");
	exit(0);
}

