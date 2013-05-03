/*!
 * \file ny_pizza_ingredient_factory.h
 * \brief The NY_Pizza_Ingredient_Factory class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-03
 */
/* $Id$ */

#ifndef NY_PIZZA_INGREDIENT_FACTORY_H
#define NY_PIZZA_INGREDIENT_FACTORY_H

#include "pizza_ingredient_factory.h"

class NY_Pizza_Ingredient_Factory : public Pizza_Ingredient_Factory
{
public:
    NY_Pizza_Ingredient_Factory();
    virtual ~NY_Pizza_Ingredient_Factory();

    virtual Dough *create_dough();
    virtual Sauce *create_sauce();
    virtual Cheese *create_cheese();
    virtual std::vector<std::auto_ptr<Veggies> > *create_veggies();
    virtual Pepperoni *create_pepperoni();
    virtual Clams *create_clam();
};

#endif /* NY_PIZZA_INGREDIENT_FACTORY_H */

