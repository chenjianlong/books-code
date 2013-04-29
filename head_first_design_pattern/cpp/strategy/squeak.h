/*!
 * \file squeak.h
 * \brief The Squeak class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-23
 */
/* $Id$ */

#ifndef SQUEAK_H
#define SQUEAK_H

#include "quack_behavior.h"

class Squeak : public Quack_Behavior
{
public:
    Squeak();
    virtual ~Squeak();

    virtual void quack();
};

#endif /* SQUEAK_H */

