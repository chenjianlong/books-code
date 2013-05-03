/* $Id$ */

#include <iostream>
#include "veggie_pizza.h"

using std::cout;
using std::endl;

Veggie_Pizza::Veggie_Pizza(Pizza_Ingredient_Factory *factory): factory_(factory)
{ }

Veggie_Pizza::~Veggie_Pizza()
{ }

void Veggie_Pizza::prepare()
{
    cout << "Preparing " << name_ << endl;
    dough_.reset(factory_->create_dough());
    sauce_.reset(factory_->create_sauce());
    cheese_.reset(factory_->create_cheese());
    veggies_.reset(factory_->create_veggies());
}

