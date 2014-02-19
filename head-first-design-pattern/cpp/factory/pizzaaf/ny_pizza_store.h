/*!
 * \file ny_pizza_store.h
 * \brief The NY_Pizza_Store class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-03
 */
/* $Id$ */

#ifndef NY_PIZZA_STORE_H
#define NY_PIZZA_STORE_H

#include <string>
#include "pizza_store.h"

class NY_Pizza_Store : public Pizza_Store
{
public:
    NY_Pizza_Store();
    virtual ~NY_Pizza_Store();

protected:
    virtual Pizza *create_pizza(std::string item);
};

#endif /* NY_PIZZA_STORE_H */

