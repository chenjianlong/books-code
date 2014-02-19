/*!
 * \file thin_crust_dough.h
 * \brief The Thin_Crust_Dough class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-03
 */
/* $Id$ */

#ifndef THIN_CRUST_DOUGH_H
#define THIN_CRUST_DOUGH_H

#include <string>
#include "dough.h"

class Thin_Crust_Dough : public Dough
{
public:
    Thin_Crust_Dough();
    virtual ~Thin_Crust_Dough();

    virtual std::string to_string();
};

#endif /* THIN_CRUST_DOUGH_H */

