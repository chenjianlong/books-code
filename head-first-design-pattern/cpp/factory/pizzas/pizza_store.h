/*!
 * \file pizza_store.h
 * \brief The Pizza_Store class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-30
 */
/* $Id$ */

#ifndef PIZZA_STORE_H
#define PIZZA_STORE_H

#include <string>
#include "simple_pizza_factory.h"

class Pizza_Store
{
public:
    Pizza_Store(Simple_Pizza_Factory &factory);
    virtual ~Pizza_Store();

	Pizza *order_pizza(std::string type);
protected:
	Simple_Pizza_Factory &factory_;
};

#endif /* PIZZA_STORE_H */

