/* $Id$ */

#include "clam_pizza.h"

Clam_Pizza::Clam_Pizza()
{
	name_ = "Clam Pizza";
	dough_ = "Thin crust";
	sauce_ = "White garlic souce";
	toppings_.push_back("Clams");
	toppings_.push_back("Grated parmesan cheese");
}

Clam_Pizza::~Clam_Pizza()
{ }

