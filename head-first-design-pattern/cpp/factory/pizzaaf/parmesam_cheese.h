/*!
 * \file parmesam_cheese.h
 * \brief The Parmesam_Cheese class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef PARMESAM_CHEESE_H
#define PARMESAM_CHEESE_H

#include <string>
#include "cheese.h"

class Parmesam_Cheese : public Cheese
{
public:
    Parmesam_Cheese();
    virtual ~Parmesam_Cheese();

    virtual std::string to_string();
};

#endif /* PARMESAM_CHEESE_H */

