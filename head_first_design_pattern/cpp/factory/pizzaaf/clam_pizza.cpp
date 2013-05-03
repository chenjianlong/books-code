/* $Id$ */

#include <iostream>
#include "clam_pizza.h"

using std::cout;
using std::endl;

Clam_Pizza::Clam_Pizza(Pizza_Ingredient_Factory *factory) : factory_(factory)
{ }

Clam_Pizza::~Clam_Pizza()
{ }

void Clam_Pizza::prepare()
{
    cout << "Preparing " << endl;
    dough_.reset(factory_->create_dough());
    sauce_.reset(factory_->create_sauce());
    cheese_.reset(factory_->create_cheese());
    clam_.reset(factory_->create_clam());
}

