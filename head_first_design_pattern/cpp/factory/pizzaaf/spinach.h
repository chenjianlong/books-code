/*!
 * \file spinach.h
 * \brief The Spinach class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef SPINACH_H
#define SPINACH_H

#include <string>
#include "Veggies.h"

class Spinach : public Veggies
{
public:
    Spinach();
    virtual ~Spinach();

    virtual std::string to_string();
};

#endif /* SPINACH_H */

