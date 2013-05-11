/* $Id$ */

#include <iostream>
#include "wild_turkey.h"

using std::cout;
using std::endl;

Wild_Turkey::Wild_Turkey()
{ }

Wild_Turkey::~Wild_Turkey()
{ }

void Wild_Turkey::gobble()
{
	cout << "Gobble gobble" << endl;
}

void Wild_Turkey::fly()
{
	cout << "I'm flying a short distance" << endl;
}

