/*!
 * \file quack.h
 * \brief The Quack class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-23
 */
/* $Id$ */

#ifndef QUACK_H
#define QUACK_H

#include "quack_behavior.h"

class Quack : public Quack_Behavior
{
public:
    Quack();
    virtual ~Quack();
    virtual void quack();
};

#endif /* QUACK_H */
