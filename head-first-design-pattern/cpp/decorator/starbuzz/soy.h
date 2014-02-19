/*!
 * \file soy.h
 * \brief The Soy class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-30
 */
/* $Id$ */

#ifndef SOY_H
#define SOY_H


#include <string>
#include "condiment_decorator.h"

class Soy : public Condiment_Decorator
{
public:
    Soy(Beverage *beverage);
    virtual ~Soy();

	virtual std::string get_description();

	virtual double cost();

private:
	Beverage *beverage_;
};

#endif /* SOY_H */

