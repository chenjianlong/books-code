/*!
 * \file sliced_pepperoni.h
 * \brief The Sliced_Pepperoni class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef SLICED_PEPPERONI_H
#define SLICED_PEPPERONI_H

#include <string>
#include "pepperoni.h"

class Sliced_Pepperoni : public Pepperoni
{
public:
    Sliced_Pepperoni();
    virtual ~Sliced_Pepperoni();

    virtual std::string to_string();
};

#endif /* SLICED_PEPPERONI_H */

