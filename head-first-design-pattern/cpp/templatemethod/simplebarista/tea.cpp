/* $Id$ */

#include <iostream>
#include "tea.h"

using std::cout;
using std::endl;

Tea::Tea()
{ }

Tea::~Tea()
{ }

void Tea::prepare_recipe()
{
	boil_water();
	steep_tea_bag();
	pour_in_cup();
	add_lemon();
}

void Tea::boil_water()
{
	cout << "Boiling water" << endl;
}

void Tea::steep_tea_bag()
{
	cout << "Steeping the tea" << endl;
}

void Tea::add_lemon()
{
	cout << "Add Lemon" << endl;
}

void Tea::pour_in_cup()
{
	cout << "Pouring into cup" << endl;
}

