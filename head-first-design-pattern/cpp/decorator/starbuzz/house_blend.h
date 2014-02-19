/*!
 * \file house_blend.h
 * \brief The House_Blend class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-30
 */
/* $Id$ */

#ifndef HOUSE_BLEND_H
#define HOUSE_BLEND_H

#include "beverage.h"

class House_Blend : public Beverage
{
public:
    House_Blend();
    virtual ~House_Blend();

	virtual double cost();
};

#endif /* HOUSE_BLEND_H */

