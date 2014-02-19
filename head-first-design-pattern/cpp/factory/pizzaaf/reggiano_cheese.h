/*!
 * \file reggiano_cheese.h
 * \brief The Reggiano_Cheese class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef REGGIANO_CHEESE_H
#define REGGIANO_CHEESE_H

#include <string>
#include "cheese.h"

class Reggiano_Cheese : public Cheese
{
public:
    Reggiano_Cheese();
    virtual ~Reggiano_Cheese();

    virtual std::string to_string();
};

#endif /* REGGIANO_CHEESE_H */

