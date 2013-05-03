/* $Id$ */

#include <iostream>
#include <string>
#include <memory>
#include "pizza_store.h"

using std::cout;
using std::endl;
using std::string;
using std::auto_ptr;

Pizza_Store::Pizza_Store()
{ }

Pizza_Store::~Pizza_Store()
{ }

Pizza *Pizza_Store::order_pizza(string type)
{
    auto_ptr<Pizza> pizza(create_pizza(type));
    cout << "--- Making a " << pizza->get_name() << " ---" <<endl;
    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();

    return pizza.release();
}
