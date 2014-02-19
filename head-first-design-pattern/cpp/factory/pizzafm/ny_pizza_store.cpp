/* $Id$ */

#include "ny_pizza_store.h"
#include "ny_style_cheese_pizza.h"
#include "ny_style_veggie_pizza.h"
#include "ny_style_clam_pizza.h"
#include "ny_style_pepperoni_pizza.h"

NY_Pizza_Store::NY_Pizza_Store()
{ }

NY_Pizza_Store::~NY_Pizza_Store()
{ }

Pizza *NY_Pizza_Store::create_pizza(std::string item)
{
	if ("cheese" == item) {
		return new NY_Style_Cheese_Pizza();
	} else if ("veggie" == item) {
		return new NY_Style_Veggie_Pizza();
	} else if ("clam" == item) {
		return new NY_Style_Clam_Pizza();
	} else if ("pepperoni" == item) {
		return new NY_Style_Pepperoni_Pizza();
	} else {
		return NULL;
	}
}

