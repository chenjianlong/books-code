/*!
 * \file clam_pizza.h
 * \brief The Clam_Pizza class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-03
 */
/* $Id$ */

#ifndef CLAM_PIZZA_H
#define CLAM_PIZZA_H

#include <memory>
#include "pizza.h"
#include "pizza_ingredient_factory.h"

class Clam_Pizza : public Pizza
{
public:
    Clam_Pizza(Pizza_Ingredient_Factory *factory);
    virtual ~Clam_Pizza();

    virtual void prepare();

protected:
    std::auto_ptr<Pizza_Ingredient_Factory> factory_;
};

#endif /* CLAM_PIZZA_H */

