/* $Id$ */

#include "decaf.h"

Decaf::Decaf() : Beverage("Decaf Coffee")
{ }

Decaf::~Decaf()
{ }

double Decaf::cost()
{
	return 1.05;
}

