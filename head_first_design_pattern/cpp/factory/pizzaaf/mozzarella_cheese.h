/*!
 * \file mozzarella_cheese.h
 * \brief The Mozzarella_Cheese class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef MOZZARELLA_CHEESE_H
#define MOZZARELLA_CHEESE_H

#include <string>
#include "cheese.h"

class Mozzarella_Cheese : public Cheese
{
public:
    Mozzarella_Cheese();
    virtual ~Mozzarella_Cheese();

    virtual std::string to_string();
};

#endif /* MOZZARELLA_CHEESE_H */

