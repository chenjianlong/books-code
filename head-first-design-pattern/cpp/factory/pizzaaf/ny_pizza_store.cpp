/* $Id$ */

#include <string>
#include <memory>
#include "ny_pizza_store.h"
#include "ny_pizza_ingredient_factory.h"
#include "cheese_pizza.h"
#include "veggie_pizza.h"
#include "clam_pizza.h"
#include "pepperoni_pizza.h"

using std::string;
using std::auto_ptr;

NY_Pizza_Store::NY_Pizza_Store()
{ }

NY_Pizza_Store::~NY_Pizza_Store()
{ }

Pizza *NY_Pizza_Store::create_pizza(string item)
{
    auto_ptr<Pizza> pizza;
    auto_ptr<Pizza_Ingredient_Factory> factory(new NY_Pizza_Ingredient_Factory());

    if ("cheese" == item) {
        pizza.reset(new Cheese_Pizza(factory.release()));
        pizza->set_name("New York Style Cheese Pizza");
    } else if ("veggie" == item) {
        pizza.reset(new Veggie_Pizza(factory.release()));
        pizza->set_name("New York Style Veggie Pizza");
    } else if ("clam" == item) {
        pizza.reset(new Clam_Pizza(factory.release()));
        pizza->set_name("New York Style Pepperoni Pizza");
    } else if ("pepperoni" == item) {
        pizza.reset(new Pepperoni_Pizza(factory.release()));
        pizza->set_name("New York Style Pepperoni Pizza");
    }

    return pizza.release();
}

