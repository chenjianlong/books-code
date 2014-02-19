/* $Id$ */

#include <iostream>
#include "coffee.h"

using std::cout;
using std::endl;

Coffee::Coffee()
{ }

Coffee::~Coffee()
{ }

void Coffee::prepare_recipe()
{
	boil_water();
	brew_coffee_grinds();
	pour_in_cup();
	add_sugar_and_milk();
}

void Coffee::boil_water()
{
	cout << "Boiling water" << endl;
}

void Coffee::brew_coffee_grinds()
{
	cout << "Dripping Coffee through filter" << endl;
}

void Coffee::pour_in_cup()
{
	cout << "Pouring into cup" << endl;
}

void Coffee::add_sugar_and_milk()
{
	cout << "Adding Sugar and Milk" << endl;
}

