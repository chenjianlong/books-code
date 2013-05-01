/*!
 * \file pizza_store.h
 * \brief The Pizza_Store class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-01
 */
/* $Id$ */

#ifndef PIZZA_STORE_H
#define PIZZA_STORE_H

#include <string>
#include "pizza.h"

class Pizza_Store
{
public:
    Pizza_Store();
    virtual ~Pizza_Store();

	virtual Pizza *create_pizza(std::string item) = 0;
	virtual Pizza *order_pizza(std::string type);
};

#endif /* PIZZA_STORE_H */

