/*!
 * \file veggie_pizza.h
 * \brief The Veggie_Pizza class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-03
 */
/* $Id$ */

#ifndef VEGGIE_PIZZA_H
#define VEGGIE_PIZZA_H

#include <memory>
#include "pizza.h"
#include "pizza_ingredient_factory.h"

class Veggie_Pizza : public Pizza
{
public:
    Veggie_Pizza(Pizza_Ingredient_Factory *factory);
    virtual ~Veggie_Pizza();

    virtual void prepare();

protected:
    std::auto_ptr<Pizza_Ingredient_Factory> factory_;
};

#endif /* VEGGIE_PIZZA_H */

