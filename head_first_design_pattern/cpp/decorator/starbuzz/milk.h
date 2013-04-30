/*!
 * \file milk.h
 * \brief The Milk class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-30
 */
/* $Id$ */

#ifndef MILK_H
#define MILK_H

#include <string>
#include "condiment_decorator.h"

class Milk : public Condiment_Decorator
{
public:
    Milk(Beverage *beverage);
    virtual ~Milk();

	virtual std::string get_description();

	virtual double cost();

private:
	Beverage *beverage_;
};

#endif /* MILK_H */

