/* $Id$ */

#include <iostream>
#include "chicago_style_cheese_pizza.h"

using std::cout;
using std::endl;

Chicago_Style_Cheese_Pizza::Chicago_Style_Cheese_Pizza()
{
	name_ = "Chicago Style Deep Dish Cheese Pizza";
	dough_ = "Extra Thick Crust Dough";
	sauce_ = "Plum Tomato Sauce";

	toppings_.push_back("Shredded Mozzarella Cheese");
}

Chicago_Style_Cheese_Pizza::~Chicago_Style_Cheese_Pizza()
{ }

void Chicago_Style_Cheese_Pizza::cut()
{
	cout << "Cutting the pizza into square slices" << endl;
}

