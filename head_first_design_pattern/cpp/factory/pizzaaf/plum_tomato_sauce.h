/*!
 * \file plum_tomato_sauce.h
 * \brief The Plum_Tomato_Sauce class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef PLUM_TOMATO_SAUCE_H
#define PLUM_TOMATO_SAUCE_H

#include <string>
#include "sauce.h"

class Plum_Tomato_Sauce : public Sauce
{
public:
    Plum_Tomato_Sauce();
    virtual ~Plum_Tomato_Sauce();

    virtual std::string to_string();
};

#endif /* PLUM_TOMATO_SAUCE_H */

