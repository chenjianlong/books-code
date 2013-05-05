/*!
 * \file pizza_ingredient_factory.h
 * \brief The Pizza_Ingredient_Factory interface. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-03
 */
/* $Id$ */

#ifndef PIZZA_INGREDIENT_FACTORY_H
#define PIZZA_INGREDIENT_FACTORY_H

#include "dough.h"
#include "sauce.h"
#include "cheese.h"
#include "veggies.h"
#include "pepperoni.h"
#include "clams.h"

class Pizza_Ingredient_Factory
{
public:
    Pizza_Ingredient_Factory() { };
    virtual ~Pizza_Ingredient_Factory() { };

    virtual Dough* create_dough() = 0;
    virtual Sauce* create_sauce() = 0;
    virtual Cheese* create_cheese() = 0;
    virtual VEGGIES_VEC *create_veggies() = 0;
    virtual Pepperoni* create_pepperoni() = 0;
    virtual Clams* create_clam() = 0;
};

#endif /* PIZZA_INGREDIENT_FACTORY_H */

