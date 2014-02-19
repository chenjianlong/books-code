/*!
 * \file espresso.h
 * \brief The Espresso class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-30
 */
/* $Id$ */

#ifndef ESPRESSO_H
#define ESPRESSO_H

#include "beverage.h"

class Espresso : public Beverage
{
public:
    Espresso();
    virtual ~Espresso();

	virtual double cost();
};

#endif /* ESPRESSO_H */

