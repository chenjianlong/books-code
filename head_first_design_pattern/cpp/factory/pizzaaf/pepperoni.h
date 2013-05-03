/*!
 * \file pepperoni.h
 * \brief The Pepperoni interface. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef PEPPERONI_H
#define PEPPERONI_H

#include <string>

class Pepperoni
{
public:
    Pepperoni() { };
    virtual ~Pepperoni() { };

    virtual std::string to_string() = 0;
};

#endif /* PEPPERONI_H */

