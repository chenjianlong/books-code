/*!
 * \file black_olives.h
 * \brief The Black_Olives class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef BLACK_OLIVES_H
#define BLACK_OLIVES_H

#include <string>
#include "veggies.h"

class Black_Olives : public Veggies
{
public:
    Black_Olives();
    virtual ~Black_Olives();

    virtual std::string to_string();
};

#endif /* BLACK_OLIVES_H */

