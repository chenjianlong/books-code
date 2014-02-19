/* $Id$ */

#include <iostream>
#include "chicago_style_veggie_pizza.h"

using std::cout;
using std::endl;

Chicago_Style_Veggie_Pizza::Chicago_Style_Veggie_Pizza()
{ 
	name_ = "Chicago Deep Dish Veggie Pizza";
	dough_ = "Extra Thick Crust Dough";
	sauce_ = "Plum Tomato Sauce";

	toppings_.push_back("Shredded Mozzarella Cheese");
	toppings_.push_back("Black Olives");
	toppings_.push_back("Spinach");
	toppings_.push_back("Eggplant");
}

Chicago_Style_Veggie_Pizza::~Chicago_Style_Veggie_Pizza()
{ }

void Chicago_Style_Veggie_Pizza::cut()
{
	cout << "Cutting the pizza into square slices" << endl;
}
