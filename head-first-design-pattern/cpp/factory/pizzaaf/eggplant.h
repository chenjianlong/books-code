/*!
 * \file eggplant.h
 * \brief The Eggplant class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef EGGPLANT_H
#define EGGPLANT_H

#include <string>
#include "veggies.h"

class Eggplant : public Veggies
{
public:
    Eggplant();
    virtual ~Eggplant();

    virtual std::string to_string();
};

#endif /* EGGPLANT_H */

