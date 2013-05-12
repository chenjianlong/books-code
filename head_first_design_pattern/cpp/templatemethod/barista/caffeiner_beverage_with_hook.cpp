/* $Id$ */

#include <iostream>
#include "caffeiner_beverage_with_hook.h"

using std::cout;
using std::endl;

Caffeiner_Beverage_With_Hook::Caffeiner_Beverage_With_Hook()
{ }

Caffeiner_Beverage_With_Hook::~Caffeiner_Beverage_With_Hook()
{ }

void Caffeiner_Beverage_With_Hook::prepare_recipe()
{
	boil_water();
	brew();
	pour_in_cup();
	if (customer_wants_condiments()) {
		add_condiments();
	}
}

void Caffeiner_Beverage_With_Hook::boil_water()
{
	cout << "Boiling water" << endl;
}

void Caffeiner_Beverage_With_Hook::pour_in_cup()
{
	cout << "Pouring into cup" << endl;
}

bool Caffeiner_Beverage_With_Hook::customer_wants_condiments()
{
	return true;
}

