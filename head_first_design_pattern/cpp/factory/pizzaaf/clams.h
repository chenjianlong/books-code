/*!
 * \file clams.h
 * \brief The Clams interface. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef CLAMS_H
#define CLAMS_H

#include <string>

class Clams
{
public:
    Clams() { };
    virtual ~Clams() { };

    virtual std::string to_string() = 0;
};

#endif /* CLAMS_H */

