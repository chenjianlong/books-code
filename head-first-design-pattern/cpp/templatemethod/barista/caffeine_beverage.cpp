/* $Id$ */

#include <iostream>
#include "caffeine_beverage.h"

using std::cout;
using std::endl;

Caffeine_Beverage::Caffeine_Beverage()
{ }

Caffeine_Beverage::~Caffeine_Beverage()
{ }

void Caffeine_Beverage::prepare_recipe()
{
	boil_water();
	brew();
	pour_in_cup();
	add_condiments();
}

void Caffeine_Beverage::boil_water()
{
	cout << "Boiling water" << endl;
}

void Caffeine_Beverage::pour_in_cup()
{
	cout << "Pouring into cup" << endl;
}

