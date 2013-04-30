/* $Id$ */

#include "espresso.h"

Espresso::Espresso() : Beverage("Espresso")
{ }

Espresso::~Espresso()
{ }

double Espresso::cost()
{
	return 1.99;
}

