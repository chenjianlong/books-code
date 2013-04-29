/*!
 * \file mute_quack.h
 * \brief The Mute_Quack class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-29
 */
/* $Id$ */

#ifndef MUTE_QUACK_H
#define MUTE_QUACK_H

#include "quack_behavior.h"

class Mute_Quack : public Quack_Behavior
{
public:
    Mute_Quack();
    virtual ~Mute_Quack();

    virtual void quack();
};

#endif /* MUTE_QUACK_H */

