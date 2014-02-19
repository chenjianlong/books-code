/*!
 * \file fly_rocket_powered.h
 * \brief The Fly_Rocket_Powered class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-29
 */
/* $Id$ */

#ifndef FLY_ROCKET_POWERED_H
#define FLY_ROCKET_POWERED_H

#include "fly_behavior.h"

class Fly_Rocket_Powered : public Fly_Behavior
{
public:
    Fly_Rocket_Powered();
    virtual ~Fly_Rocket_Powered();

    virtual void fly();

};

#endif /* FLY_ROCKET_POWERED_H */

