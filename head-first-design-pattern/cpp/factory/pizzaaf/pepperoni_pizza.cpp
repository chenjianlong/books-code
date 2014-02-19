/* $Id$ */

#include <iostream>
#include "pepperoni_pizza.h"

using std::cout;
using std::endl;

Pepperoni_Pizza::Pepperoni_Pizza(Pizza_Ingredient_Factory *factory) : factory_(factory)
{ }

Pepperoni_Pizza::~Pepperoni_Pizza()
{ }

void Pepperoni_Pizza::prepare()
{
    cout << "Preparing " << name_ << endl;
    dough_.reset(factory_->create_dough());
    sauce_.reset(factory_->create_sauce());
    cheese_.reset(factory_->create_cheese());
    veggies_.reset(factory_->create_veggies());
    pepperoni_.reset(factory_->create_pepperoni());
}

