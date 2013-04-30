/*!
 * \file whip.h
 * \brief The Whip class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-30
 */
/* $Id$ */

#ifndef WHIP_H
#define WHIP_H

#include <string>
#include "condiment_decorator.h"

class Whip : public Condiment_Decorator
{
public:
    Whip(Beverage *beverage);
    virtual ~Whip();

	virtual std::string get_description();

	virtual double cost();

private:
	Beverage *beverage_;
};

#endif /* WHIP_H */

