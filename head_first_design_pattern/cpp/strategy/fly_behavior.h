/*!
 * \file fly_behavior.h
 * \brief The Fly_Behavior class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-23
 */
/* $Id$ */

#ifndef FLY_BEHAVIOR_H
#define FLY_BEHAVIOR_H

class Fly_Behavior
{
public:
    Fly_Behavior() {}
    virtual ~Fly_Behavior() {}
    
    virtual void fly() = 0;
};

#endif /* FLY_BEHAVIOR_H */
