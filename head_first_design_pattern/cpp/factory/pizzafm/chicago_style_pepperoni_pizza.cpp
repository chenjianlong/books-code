/* $Id$ */

#include <iostream>
#include "chicago_style_pepperoni_pizza.h"

using std::cout;
using std::endl;

Chicago_Style_Pepperoni_Pizza::Chicago_Style_Pepperoni_Pizza()
{
	name_ = "Chicago Style Pepperoni Pizza";
	dough_ = "Extra Thick Crust Dough";
	sauce_ = "Plum Tomato Sauce";

	toppings_.push_back("Shredded Mozzarella Cheese");
	toppings_.push_back("Black Olives");
	toppings_.push_back("Spinach");
	toppings_.push_back("Eggplant");
	toppings_.push_back("Sliced Pepperoni");
}

Chicago_Style_Pepperoni_Pizza::~Chicago_Style_Pepperoni_Pizza()
{ }

void Chicago_Style_Pepperoni_Pizza::cut()
{
	cout << "Cutting the pizza into square slices" << endl;
}

