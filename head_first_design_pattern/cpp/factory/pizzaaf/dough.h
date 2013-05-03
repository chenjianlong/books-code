/*!
 * \file dough.h
 * \brief The Dough interface. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef DOUGH_H
#define DOUGH_H

#include <string>

class Dough
{
public:
    Dough() { };
    virtual ~Dough() { };

    virtual std::string to_string() = 0;
};

#endif /* DOUGH_H */

