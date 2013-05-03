/* $Id$ */

#include <iostream>
#include "cheese_pizza.h"

using std::cout;
using std::endl;

Cheese_Pizza::Cheese_Pizza(Pizza_Ingredient_Factory *factory) : factory_(factory)
{ }

Cheese_Pizza::~Cheese_Pizza()
{ }

void Cheese_Pizza::prepare()
{
    cout << "Preparing " << name_ << endl;
    dough_.reset(factory_->create_dough());
    sauce_.reset(factory_->create_sauce());
    cheese_.reset(factory_->create_cheese());
}

