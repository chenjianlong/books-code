/* $Id$ */

#include <iostream>
#include "barista.h"
#include "tea.h"
#include "coffee.h"

using std::cout;
using std::endl;

Barista::Barista()
{ }

Barista::~Barista()
{ }

int Barista::main(int argc, char * argv[])
{
	Tea tea;
	Coffee coffee;

	cout << "Making tea..." << endl;
	tea.prepare_recipe();

	cout << "Making coffee..." << endl;
	coffee.prepare_recipe();

	return 0;
}

