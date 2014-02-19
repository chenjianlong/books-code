/*!
 * \file onion.h
 * \brief The Onion class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef ONION_H
#define ONION_H

#include <string>
#include "veggies.h"

class Onion : public Veggies
{
public:
    Onion();
    virtual ~Onion();

    virtual std::string to_string();
};

#endif /* ONION_H */

