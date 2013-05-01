/*!
 * \file simple_pizza_factory.h
 * \brief The Simple_Pizza_Factory class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-30
 */
/* $Id$ */

#ifndef SIMPLE_PIZZA_FACTORY_H
#define SIMPLE_PIZZA_FACTORY_H

#include <string>
#include "pizza.h"

class Simple_Pizza_Factory
{
public:
    Simple_Pizza_Factory();
    virtual ~Simple_Pizza_Factory();

	virtual Pizza *create_pizza(std::string type);
};

#endif /* SIMPLE_PIZZA_FACTORY_H */

