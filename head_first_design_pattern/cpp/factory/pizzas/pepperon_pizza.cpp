/* $Id$ */

#include "pepperon_pizza.h"

Pepperon_Pizza::Pepperon_Pizza()
{
	name_ = "Pepperoni Pizza";
	dough_ = "Crust";
	sauce_ = "Marinara souce";
	toppings_.push_back("Sliced Pepperoni");
	toppings_.push_back("Sliced Onion");
	toppings_.push_back("Grated parmesan cheese");
}

Pepperon_Pizza::~Pepperon_Pizza()
{ }

