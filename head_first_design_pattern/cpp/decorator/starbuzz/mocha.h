/*!
 * \file mocha.h
 * \brief The Mocha class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-30
 */
/* $Id$ */

#ifndef MOCHA_H
#define MOCHA_H

#include <string>
#include "condiment_decorator.h"

class Mocha : public Condiment_Decorator
{
public:
    Mocha(Beverage *beverage);
    virtual ~Mocha();

	virtual std::string get_description();

	virtual double cost();

private:
	Beverage *beverage_;
};

#endif /* MOCHA_H */

