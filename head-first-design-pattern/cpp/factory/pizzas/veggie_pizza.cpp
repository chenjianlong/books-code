/* $Id$ */

#include "veggie_pizza.h"

Veggie_Pizza::Veggie_Pizza()
{
	name_ = "Veggie Pizza";
	dough_ = "Crust";
	sauce_ = "Marinara sauce";
	toppings_.push_back("Shredded mozzarella");
	toppings_.push_back("Grated parmesan");
	toppings_.push_back("Diced onion");
	toppings_.push_back("Sliced mushrooms");
	toppings_.push_back("Sliced red pepper");
	toppings_.push_back("Sliced black olives");
}

Veggie_Pizza::~Veggie_Pizza()
{ }

