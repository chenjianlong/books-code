/*!
 * \file frozen_clams.h
 * \brief The Frozen_Clams class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef FROZEN_CLAMS_H
#define FROZEN_CLAMS_H

#include <string>
#include "clams.h"

class Frozen_Clams : public Clams
{
public:
    Frozen_Clams();
    virtual ~Frozen_Clams();

    virtual std::string to_string();
};

#endif /* FROZEN_CLAMS_H */

