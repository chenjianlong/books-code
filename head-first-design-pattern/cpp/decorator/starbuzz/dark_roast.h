/*!
 * \file dark_roast.h
 * \brief The Dark_Roast class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-30
 */
/* $Id$ */

#ifndef DARK_ROAST_H
#define DARK_ROAST_H

#include "beverage.h"

class Dark_Roast : public Beverage
{
public:
    Dark_Roast();
    virtual ~Dark_Roast();

	virtual double cost();
};

#endif /* DARK_ROAST_H */

