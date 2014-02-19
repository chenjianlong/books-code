/*!
 * \file red_pepper.h
 * \brief The Red_Pepper class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef RED_PEPPER_H
#define RED_PEPPER_H

#include <string>
#include "veggies.h"

class Red_Pepper : public Veggies
{
public:
    Red_Pepper();
    virtual ~Red_Pepper();

    virtual std::string to_string();
};

#endif /* RED_PEPPER_H */

