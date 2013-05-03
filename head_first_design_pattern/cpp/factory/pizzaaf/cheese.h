/*!
 * \file cheese.h
 * \brief The Cheese interface. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef CHEESE_H
#define CHEESE_H

#include <string>

class Cheese
{
public:
    Cheese() { };
    virtual ~Cheese() { };

    virtual std::string to_string() = 0;
};

#endif /* CHEESE_H */

