/* $Id$ */

#include "simple_pizza_factory.h"
#include "cheese_pizza.h"
#include "pepperon_pizza.h"
#include "clam_pizza.h"
#include "veggie_pizza.h"

Simple_Pizza_Factory::Simple_Pizza_Factory()
{ }

Simple_Pizza_Factory::~Simple_Pizza_Factory()
{ }

Pizza *Simple_Pizza_Factory::create_pizza(std::string type)
{
	Pizza *pizza = NULL;

	if ("cheese" == type) {
		pizza = new Cheese_Pizza();
	} else if ("pepperoni" == type) {
		pizza = new Pepperon_Pizza();
	} else if ("clam" == type) {
		pizza = new Clam_Pizza();
	} else if ("veggie" == type) {
		pizza = new Veggie_Pizza();
	}
	return pizza;
}

