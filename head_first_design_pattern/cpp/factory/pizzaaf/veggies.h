/*!
 * \file veggies.h
 * \brief The Veggies interface. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef VEGGIES_H
#define VEGGIES_H

#include <string>

class Veggies
{
public:
    Veggies() { };
    virtual ~Veggies() { };

    virtual std::string to_string() = 0;
};

#endif /* VEGGIES_H */

