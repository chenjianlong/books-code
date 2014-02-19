/*!
 * \file sauce.h
 * \brief The Sauce interface. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef SAUCE_H
#define SAUCE_H

#include <string>

class Sauce
{
public:
    Sauce() { };
    virtual ~Sauce() { };

    virtual std::string to_string() = 0;
};

#endif /* SAUCE_H */

