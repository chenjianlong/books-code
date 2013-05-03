/*!
 * \file garlic.h
 * \brief The Garlic class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef GARLIC_H
#define GARLIC_H

#include <string>
#include "veggies.h"

class Garlic : public Veggies
{
public:
    Garlic();
    virtual ~Garlic();

    virtual std::string to_string();
};

#endif /* GARLIC_H */

