/* $Id$ */

#include <iostream>
#include "pizza_store.h"

using std::cout;
using std::endl;
using std::string;

Pizza_Store::Pizza_Store()
{ }

Pizza_Store::~Pizza_Store()
{ }

Pizza *Pizza_Store::order_pizza(std::string type)
{
	Pizza *pizza = create_pizza(type);
	cout << "--- Making a " << pizza->get_name() << " ---" << endl;
	pizza->prepare();
	pizza->bake();
	pizza->cut();
	pizza->box();
	return pizza;
}
