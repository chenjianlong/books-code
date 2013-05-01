/* $Id$ */

#include <iostream>
#include "pizza_test_drive.h"
#include "chicago_pizza_store.h"
#include "ny_pizza_store.h"

using std::cout;
using std::endl;

Pizza_Test_Drive::Pizza_Test_Drive()
{ }

Pizza_Test_Drive::~Pizza_Test_Drive()
{ }

int Pizza_Test_Drive::main(int argc, char *argv[])
{
	Pizza_Store *ny_store = new NY_Pizza_Store();
	Pizza_Store *chicago_store = new Chicago_Pizza_Store();

	Pizza *pizza = ny_store->order_pizza("cheese");
	cout << "Ethan ordered a " << pizza->get_name() << endl;
	delete pizza;

	pizza = chicago_store->order_pizza("cheese");
	cout << "Joel ordered a " << pizza->get_name() << endl;
	delete pizza;

	pizza = ny_store->order_pizza("clam");
	cout << "Ethan ordered a " << pizza->get_name() << endl;
	delete pizza;

	pizza = chicago_store->order_pizza("clam");
	cout << "Joel ordered a " << pizza->get_name() << endl;
	delete pizza;

	pizza = ny_store->order_pizza("pepperoni");
	cout << "Ethan ordered a " << pizza->get_name() << endl;
	delete pizza;

	pizza = chicago_store->order_pizza("pepperoni");
	cout << "Joel ordered a " << pizza->get_name() << endl;
	delete pizza;

	pizza = ny_store->order_pizza("veggie");
	cout << "Ethan ordered a " << pizza->get_name() << endl;
	delete pizza;

	pizza = chicago_store->order_pizza("veggie");
	cout << "Joel ordered a " << pizza->get_name() << endl;
	delete pizza;

	return 0;
}

