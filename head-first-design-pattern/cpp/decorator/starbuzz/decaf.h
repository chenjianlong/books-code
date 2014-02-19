/*!
 * \file decaf.h
 * \brief The Decaf class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-30
 */
/* $Id$ */

#ifndef DECAF_H
#define DECAF_H

#include "beverage.h"

class Decaf : public Beverage
{
public:
    Decaf();
    virtual ~Decaf();

	virtual double cost();
};

#endif /* DECAF_H */

