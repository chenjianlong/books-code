/* $Id$ */

#include <iostream>
#include "coffee.h"

using std::cout;
using std::endl;

Coffee::Coffee()
{ }

Coffee::~Coffee()
{ }

void Coffee::brew()
{
	cout << "Dripping Coffee through filter" << endl;
}

void Coffee::add_condiments()
{
	cout << "Adding Suger and Milk" << endl;
}

