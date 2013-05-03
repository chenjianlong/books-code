/* $Id$ */

#include "ny_pizza_ingredient_factory.h"
#include "thin_crust_dough.h"
#include "marinara_sauce.h"
#include "reggiano_cheese.h"
#include "garlic.h"
#include "onion.h"
#include "mushroom.h"
#include "red_pepper.h"
#include "sliced_pepperoni.h"
#include "fresh_clams.h"

using std::vector;
using std::auto_ptr;

NY_Pizza_Ingredient_Factory::NY_Pizza_Ingredient_Factory()
{ }

NY_Pizza_Ingredient_Factory::~NY_Pizza_Ingredient_Factory()
{ }

Dough *NY_Pizza_Ingredient_Factory::create_dough()
{
    return new Thin_Crust_Dough();
}

Sauce *NY_Pizza_Ingredient_Factory::create_sauce()
{
    return new Marinara_Sauce();
}

Cheese *NY_Pizza_Ingredient_Factory::create_cheese()
{
    return new Reggiano_Cheese();
}

std::vector<std::auto_ptr<Veggies> > *NY_Pizza_Ingredient_Factory::create_veggies()
{
    auto_ptr<vector<auto_ptr<Veggies> > > veggies(new std::vector<std::auto_ptr<Veggies> >());
    veggies->push_back(auto_ptr<Veggies>(new Garlic()));
    veggies->push_back(auto_ptr<Veggies>(new Onion()));
    veggies->push_back(auto_ptr<Veggies>(new Mushroom()));
    veggies->push_back(auto_ptr<Veggies>(new Red_Pepper()));

    return veggies.release();
}

Pepperoni *NY_Pizza_Ingredient_Factory::create_pepperoni()
{
    return new Sliced_Pepperoni();
}

Clams *NY_Pizza_Ingredient_Factory::create_clam()
{
    return new Fresh_Clams();
}

