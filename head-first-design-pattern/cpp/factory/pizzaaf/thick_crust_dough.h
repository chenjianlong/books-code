/*!
 * \file thick_crust_dough.h
 * \brief The Thick_Crust_Dough class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef THICK_CRUST_DOUGH_H
#define THICK_CRUST_DOUGH_H

#include <string>
#include "dough.h"

class Thick_Crust_Dough : public Dough
{
public:
    Thick_Crust_Dough();
    virtual ~Thick_Crust_Dough();

    virtual std::string to_string();
};

#endif /* THICK_CRUST_DOUGH_H */

