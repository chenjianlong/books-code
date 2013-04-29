/*!
 * \file fly_with_wings.h
 * \brief The Fly_With_Wings class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-29
 */
/* $Id$ */

#ifndef FLY_WITH_WINGS_H
#define FLY_WITH_WINGS_H

#include "fly_behavior.h"
class Fly_With_Wings : public Fly_Behavior
{
public:
    Fly_With_Wings();
    virtual ~Fly_With_Wings();

    virtual void fly();
};

#endif /* FLY_WITH_WINGS_H */

