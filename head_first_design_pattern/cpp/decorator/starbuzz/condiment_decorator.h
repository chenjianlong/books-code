/*!
 * \file condiment_decorator.h
 * \brief The Condiment_Decorator class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-30
 */
/* $Id$ */

#ifndef CONDIMENT_DECORATOR_H
#define CONDIMENT_DECORATOR_H

#include <string>
#include "beverage.h"

class Condiment_Decorator : public Beverage
{
public:
    Condiment_Decorator() { };
    virtual ~Condiment_Decorator() { };

	virtual std::string get_description() = 0;
};

#endif /* CONDIMENT_DECORATOR_H */

