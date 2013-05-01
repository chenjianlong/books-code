/*!
 * \file chicago_pizza_store.h
 * \brief The Chicago_Pizza_Store class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-01
 */
/* $Id$ */

#ifndef CHICAGO_PIZZA_STORE_H
#define CHICAGO_PIZZA_STORE_H

#include <string>
#include "pizza_store.h"
#include "pizza.h"

class Chicago_Pizza_Store : public Pizza_Store
{
public:
    Chicago_Pizza_Store();
    virtual ~Chicago_Pizza_Store();

	virtual Pizza *create_pizza(std::string item);
};

#endif /* CHICAGO_PIZZA_STORE_H */

