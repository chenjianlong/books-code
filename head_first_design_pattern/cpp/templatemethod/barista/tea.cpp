/* $Id$ */

#include <iostream>
#include "tea.h"

using std::cout;
using std::endl;

Tea::Tea()
{ }

Tea::~Tea()
{ }

void Tea::brew()
{
	cout << "Steeping the tea" << endl;
}

void Tea::add_condiments()
{
	cout << "Adding Lemon" << endl;
}

