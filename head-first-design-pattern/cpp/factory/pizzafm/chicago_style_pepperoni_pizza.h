/*!
 * \file chicago_style_pepperoni_pizza.h
 * \brief The Chicago_Style_Pepperoni_Pizza class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-01
 */
/* $Id$ */

#ifndef CHICAGO_STYLE_PEPPERONI_PIZZA_H
#define CHICAGO_STYLE_PEPPERONI_PIZZA_H

#include "pizza.h"

class Chicago_Style_Pepperoni_Pizza : public Pizza
{
public:
    Chicago_Style_Pepperoni_Pizza();
    virtual ~Chicago_Style_Pepperoni_Pizza();

	virtual void cut();
};

#endif /* CHICAGO_STYLE_PEPPERONI_PIZZA_H */

