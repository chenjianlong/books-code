/* $Id$ */

#include "chicago_pizza_store.h"
#include "chicago_style_cheese_pizza.h"
#include "chicago_style_clam_pizza.h"
#include "chicago_style_pepperoni_pizza.h"
#include "chicago_style_veggie_pizza.h"

Chicago_Pizza_Store::Chicago_Pizza_Store()
{ }

Chicago_Pizza_Store::~Chicago_Pizza_Store()
{ }

Pizza *Chicago_Pizza_Store::create_pizza(std::string item)
{
	if ("cheese" == item) {
		return new Chicago_Style_Cheese_Pizza();
	} else if ("clam" == item) {
		return new Chicago_Style_Clam_Pizza();
	} else if ("pepperoni" == item) {
		return new Chicago_Style_Pepperoni_Pizza();
	} else if ("veggie" == item) {
		return new Chicago_Style_Veggie_Pizza();
	} else {
		return NULL;
	}
}

