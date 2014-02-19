/*!
 * \file fly_no_way.h
 * \brief The Fly_No_Way class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-23
 */
/* $Id$ */

#ifndef FLY_NO_WAY_H
#define FLY_NO_WAY_H

#include "fly_behavior.h"

class Fly_No_Way : public Fly_Behavior
{
public:
    Fly_No_Way();
    virtual ~Fly_No_Way();

    virtual void fly();
};

#endif /* FLY_NO_WAY_H */

