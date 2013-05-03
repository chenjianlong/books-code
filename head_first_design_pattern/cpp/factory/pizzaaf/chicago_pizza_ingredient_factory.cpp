/* $Id$ */

#include <memory>
#include <vector>
#include "chicago_pizza_ingredient_factory.h"
#include "thick_crust_dough.h"
#include "plum_tomato_sauce.h"
#include "mozzarella_cheese.h"
#include "black_olives.h"
#include "spinach.h"
#include "eggplant.h"
#include "sliced_pepperoni.h"
#include "frozen_clams.h"

using std::auto_ptr;
using std::vector;

Chicago_Pizza_Ingredient_Factory::Chicago_Pizza_Ingredient_Factory()
{ }

Chicago_Pizza_Ingredient_Factory::~Chicago_Pizza_Ingredient_Factory()
{ }

Dough *Chicago_Pizza_Ingredient_Factory::create_dough()
{
    return new Thick_Crust_Dough();
}

Sauce *Chicago_Pizza_Ingredient_Factory::create_sauce()
{
    return new Plum_Tomato_Sauce();
}

Cheese *Chicago_Pizza_Ingredient_Factory::create_cheese()
{
    return new Mozzarella_Cheese();
}

vector<auto_ptr<Veggies> > *Chicago_Pizza_Ingredient_Factory::create_veggies()
{
    auto_ptr<vector<auto_ptr<Veggies> > > veggies(new vector<auto_ptr<Veggies> >());
    veggies->push_back(auto_ptr<Veggies>(new Black_Olives()));
    veggies->push_back(auto_ptr<Veggies>(new Spinach()));
    veggies->push_back(auto_ptr<Veggies>(new Eggplant()));
    return veggies.release();
}

Pepperoni *Chicago_Pizza_Ingredient_Factory::create_pepperoni()
{
    return new Sliced_Pepperoni();
}

Clams *Chicago_Pizza_Ingredient_Factory::create_clam()
{
    return new Frozen_Clams();
}

