/*!
 * \file chicago_pizza_ingredient_factory.h
 * \brief The Chicago_Pizza_Ingredient_Factory class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-03
 */
/* $Id$ */

#ifndef CHICAGO_PIZZA_INGREDIENT_FACTORY_H
#define CHICAGO_PIZZA_INGREDIENT_FACTORY_H

#include "pizza_ingredient_factory.h"

class Chicago_Pizza_Ingredient_Factory : public Pizza_Ingredient_Factory
{
public:
    Chicago_Pizza_Ingredient_Factory();
    virtual ~Chicago_Pizza_Ingredient_Factory();

    virtual Dough* create_dough();
    virtual Sauce* create_sauce();
    virtual Cheese* create_cheese();
    virtual VEGGIES_VEC* create_veggies();
    virtual Pepperoni* create_pepperoni();
    virtual Clams* create_clam();
};

#endif /* CHICAGO_PIZZA_INGREDIENT_FACTORY_H */

