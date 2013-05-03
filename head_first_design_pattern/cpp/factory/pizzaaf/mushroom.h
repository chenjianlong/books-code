/*!
 * \file mushroom.h
 * \brief The Mushroom class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <string>
#include "veggies.h"

class Mushroom : public Veggies
{
public:
    Mushroom();
    virtual ~Mushroom();

    virtual std::string to_string();
};

#endif /* MUSHROOM_H */

