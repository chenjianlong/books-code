/* $Id$ */

#include "cheese_pizza.h"

Cheese_Pizza::Cheese_Pizza()
{ 
	name_ = "Cheese Pizza";
	dough_ = "Regular Crust";
	sauce_ = "Marinara Pizza Source";
	toppings_.push_back("Fresh Mozzarella");
	toppings_.push_back("Parmesan");
}

Cheese_Pizza::~Cheese_Pizza()
{ }

