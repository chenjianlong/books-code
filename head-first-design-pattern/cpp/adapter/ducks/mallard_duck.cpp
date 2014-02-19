/* $Id$ */

#include <iostream>
#include "mallard_duck.h"

using std::cout;
using std::endl;

Mallard_Duck::Mallard_Duck()
{ }

Mallard_Duck::~Mallard_Duck()
{ }

void Mallard_Duck::quack()
{
	cout << "Quack" << endl;
}

void Mallard_Duck::fly()
{
	cout << "I'm flying" << endl;
}

