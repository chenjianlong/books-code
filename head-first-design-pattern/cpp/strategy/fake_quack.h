/*!
 * \file fake_quack.h
 * \brief The Fake_Quack class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-23
 */
/* $Id$ */

#ifndef FAKE_QUACK_H
#define FAKE_QUACK_H

#include "quack_behavior.h"

class Fake_Quack : public Quack_Behavior
{
public:
    Fake_Quack();
    virtual ~Fake_Quack();

    virtual void quack();
};

#endif /* FAKE_QUACK_H */

