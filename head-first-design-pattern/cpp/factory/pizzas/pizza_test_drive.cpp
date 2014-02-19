/* $Id$ */

#include <iostream>
#include <string>
#include "pizza_test_drive.h"
#include "simple_pizza_factory.h"
#include "pizza_store.h"

Pizza_Test_Drive::Pizza_Test_Drive()
{ }

Pizza_Test_Drive::~Pizza_Test_Drive()
{ }

int Pizza_Test_Drive::main(int argc, char *argv[])
{
	using namespace std;

	Simple_Pizza_Factory factory;
	Pizza_Store store(factory);

	Pizza *pizza = store.order_pizza("cheese");
	cout << "We ordered a " << pizza->get_name() << endl;
	delete pizza;

	pizza = store.order_pizza("veggie");
	cout << "We ordered a " << pizza->get_name() << endl;
	delete pizza;

	return 0;
}
