/* $Id$ */

#include "ny_style_veggie_pizza.h"

NY_Style_Veggie_Pizza::NY_Style_Veggie_Pizza()
{
	name_ = "NY Style Veggie Pizza";
	dough_ = "Thin Crust Dough";
	sauce_ = "Marinara Sauce";

	toppings_.push_back("Grated Reggiano Cheese");
	toppings_.push_back("Garlic");
	toppings_.push_back("Onion");
	toppings_.push_back("Mushrooms");
	toppings_.push_back("Red Pepper");
}

NY_Style_Veggie_Pizza::~NY_Style_Veggie_Pizza()
{ }

