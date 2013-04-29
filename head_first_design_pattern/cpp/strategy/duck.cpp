/* $Id$ */

#include <iostream>
#include "duck.h"

Duck::Duck(): fb_(NULL), qb_(NULL)
{ }

Duck::~Duck()
{ 
    if (fb_) {
        delete fb_;
        fb_ = NULL;
    }

    if (qb_) {
        delete qb_;
        qb_ = NULL;
    }
}

void Duck::set_fly_behavior(Fly_Behavior *fb)
{
    fb_ = fb;
}

void Duck::set_quack_behavior(Quack_Behavior *qb)
{
    qb_ = qb;
}

void Duck::perform_fly()
{
    fb_->fly();
}

void Duck::perform_quack()
{
    qb_->quack();
}

void Duck::swim()
{
    std::cout << "All ducks float, even decoys!" << std::endl;
}
