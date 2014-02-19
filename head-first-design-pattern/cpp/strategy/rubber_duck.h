/*!
 * \file rubber_duck.h
 * \brief The Rubber_Duck class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-29
 */
/* $Id$ */

#ifndef RUBBER_DUCK_H
#define RUBBER_DUCK_H

#include "duck.h"

class Rubber_Duck : public Duck
{
public:
    Rubber_Duck();
    virtual ~Rubber_Duck();

    virtual void display();
};

#endif /* RUBBER_DUCK_H */

