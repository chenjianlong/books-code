/*!
 * \file duck.h
 * \brief The Duck class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-23
 */
/* $Id$ */

#ifndef DUCK_H
#define DUCK_H

#include "fly_behavior.h"
#include "quack_behavior.h"

class Duck
{
public:
    Duck();
    virtual ~Duck();
    
    void set_fly_behavior(Fly_Behavior *fb);
    
    void set_quack_behavior(Quack_Behavior *qb);

    virtual void display() = 0;

    void perform_fly();

    void perform_quack();

    void swim();

private:
    Fly_Behavior *fb_;
    Quack_Behavior *qb_;
};

#endif /* DUCK_H */
