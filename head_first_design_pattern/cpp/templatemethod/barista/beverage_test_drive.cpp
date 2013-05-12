/* $Id$ */

#include <iostream>
#include "beverage_test_drive.h"
#include "tea.h"
#include "coffee.h"
#include "tea_with_hook.h"
#include "coffee_with_hook.h"

using std::cout;
using std::endl;

Beverage_Test_Drive::Beverage_Test_Drive()
{ }

Beverage_Test_Drive::~Beverage_Test_Drive()
{ }

int Beverage_Test_Drive::main(int argc, char *argv[])
{
	Tea tea;
	Coffee coffee;

	cout << "\nMaking tea..." << endl;
	tea.prepare_recipe();

	cout << "\nMaking coffee..." << endl;
	coffee.prepare_recipe();

	Tea_With_Hook tea_hook;
	Coffee_With_Hook coffee_hook;

	cout << "\nMaking tea..." << endl;
	tea_hook.prepare_recipe();

	cout << "\nMaking coffee..." << endl;
	coffee_hook.prepare_recipe();

	return 0;
}

