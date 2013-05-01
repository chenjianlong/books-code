/* $Id$ */

#include <iostream>
#include "chicago_style_clam_pizza.h"

using std::cout;
using std::endl;

Chicago_Style_Clam_Pizza::Chicago_Style_Clam_Pizza()
{ 
	name_ = "Chicago Style Clam Pizza";
	dough_ = "Extra Thick Crust Dough";
	sauce_ = "Plum Tomato Sauce";

	toppings_.push_back("Shredded Mozzarella Cheese");
	toppings_.push_back("Frozen Clams from Chesapeake Bay");
}

Chicago_Style_Clam_Pizza::~Chicago_Style_Clam_Pizza()
{ }

void Chicago_Style_Clam_Pizza::cut()
{
	cout << "Cutting the pizza into square slices" << endl;
}

