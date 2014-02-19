/* $Id$ */

#include "pizza_store.h"

Pizza_Store::Pizza_Store(Simple_Pizza_Factory &factory) : factory_(factory)
{ }

Pizza_Store::~Pizza_Store()
{ }

Pizza *Pizza_Store::order_pizza(std::string type)
{
	Pizza *pizza = NULL;

	pizza = factory_.create_pizza(type);

	pizza->prepare();
	pizza->bake();
	pizza->cut();
	pizza->box();

	return pizza;
}

