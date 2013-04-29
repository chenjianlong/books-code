/*!
 * \file decoy_duck.h
 * \brief The Decoy_Duck class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-29
 */
/* $Id$ */

#ifndef DECOY_DUCK_H
#define DECOY_DUCK_H

#include "duck.h"

class Decoy_Duck : public Duck
{
public:
    Decoy_Duck();
    virtual ~Decoy_Duck();

    virtual void display();
};

#endif /* DECOY_DUCK_H */

