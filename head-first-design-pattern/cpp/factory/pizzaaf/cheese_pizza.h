/*!
 * \file cheese_pizza.h
 * \brief The Cheese_Pizza class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-03
 */
/* $Id$ */

#ifndef CHEESE_PIZZA_H
#define CHEESE_PIZZA_H

#include <memory>
#include "pizza.h"
#include "pizza_ingredient_factory.h"

class Cheese_Pizza : public Pizza
{
public:
    Cheese_Pizza(Pizza_Ingredient_Factory *factory);
    virtual ~Cheese_Pizza();

    virtual void prepare();
protected:
    std::auto_ptr<Pizza_Ingredient_Factory> factory_;
};

#endif /* CHEESE_PIZZA_H */

