/*!
 * \file fresh_clams.h
 * \brief The Fresh_Clams class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef FRESH_CLAMS_H
#define FRESH_CLAMS_H

#include <string>
#include "clams.h"

class Fresh_Clams : public Clams
{
public:
    Fresh_Clams();
    virtual ~Fresh_Clams();

    virtual std::string to_string();
};

#endif /* FRESH_CLAMS_H */

