/*!
 * \file quack_behavior.h
 * \brief The Quack_Behavior interface. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-23
 */
/* $Id$ */

#ifndef QUACK_BEHAVIOR_H
#define QUACK_BEHAVIOR_H

class Quack_Behavior
{
public:
    Quack_Behavior() {}
    virtual ~Quack_Behavior() {}

    virtual void quack() = 0;
};

#endif /* QUACK_BEHAVIOR_H */
