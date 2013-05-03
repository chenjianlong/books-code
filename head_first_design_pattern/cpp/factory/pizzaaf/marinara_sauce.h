/*!
 * \file marinara_sauce.h
 * \brief The Marinara_Sauce class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef MARINARA_SAUCE_H
#define MARINARA_SAUCE_H

#include <string>
#include "sauce.h"

class Marinara_Sauce : public Sauce
{
public:
    Marinara_Sauce();
    virtual ~Marinara_Sauce();

    virtual std::string to_string();
};

#endif /* MARINARA_SAUCE_H */

