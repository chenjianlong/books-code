/*
 * \file assert.c
 * \brief demo for assert
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-07-26
 */
/* $Id$ */

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

double my_sqrt(double x)
{
	assert(x >= 0.0);
	return sqrt(x);
}

int main()
{
	printf("sqrt +2 = %g\n", my_sqrt(2.0));
	printf("sqrt -2 = %g\n", my_sqrt(-2.0));
	exit(0);
}

