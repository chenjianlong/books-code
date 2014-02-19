/* $Id$ */

#include <memory>
#include <string>
#include "chicago_pizza_store.h"
#include "chicago_pizza_ingredient_factory.h"
#include "cheese_pizza.h"
#include "veggie_pizza.h"
#include "clam_pizza.h"
#include "pepperoni_pizza.h"

using std::auto_ptr;
using std::string;

Chicago_Pizza_Store::Chicago_Pizza_Store()
{ }

Chicago_Pizza_Store::~Chicago_Pizza_Store()
{ }

Pizza *Chicago_Pizza_Store::create_pizza(string item)
{
    auto_ptr<Pizza> pizza;
    auto_ptr<Pizza_Ingredient_Factory> factory(new Chicago_Pizza_Ingredient_Factory());

    if ("cheese" == item) {
        pizza.reset(new Cheese_Pizza(factory.release()));
        pizza->set_name("Chicago Style Cheese Pizza");
    } else if ("veggie" == item) {
        pizza.reset(new Veggie_Pizza(factory.release()));
        pizza->set_name("Chicago Style Veggie Pizza");
    } else if ("clam" == item) {
        pizza.reset(new Clam_Pizza(factory.release()));
        pizza->set_name("Chicago Style Clam Pizza");
    } else if ("pepperoni" == item) {
        pizza.reset(new Pepperoni_Pizza(factory.release()));
        pizza->set_name("Chicago Style Pepperoni Pizza");
    }
    return pizza.release();
}

