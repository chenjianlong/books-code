/*!
 * \file pepperoni_pizza.h
 * \brief The Pepperoni_Pizza class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-03
 */
/* $Id$ */

#ifndef PEPPERONI_PIZZA_H
#define PEPPERONI_PIZZA_H

#include <memory>
#include "pizza.h"
#include "pizza_ingredient_factory.h"

class Pepperoni_Pizza : public Pizza
{
public:
    Pepperoni_Pizza(Pizza_Ingredient_Factory *factory);
    virtual ~Pepperoni_Pizza();

    virtual void prepare();

protected:
    std::auto_ptr<Pizza_Ingredient_Factory> factory_;
};

#endif /* PEPPERONI_PIZZA_H */

