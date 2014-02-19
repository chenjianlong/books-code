/*!
 * \file coffee.h
 * \brief The Coffee class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef COFFEE_H
#define COFFEE_H

#include "caffeine_beverage.h"

class Coffee : public Caffeine_Beverage
{
public:
	Coffee();
	virtual ~Coffee();

	virtual void brew();
	virtual void add_condiments();
};

#endif /* COFFEE_H */

