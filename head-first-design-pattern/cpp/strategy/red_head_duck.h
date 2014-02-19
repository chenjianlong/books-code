/*!
 * \file red_head_duck.h
 * \brief The Red_Head_Duck class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-29
 */
/* $Id$ */

#ifndef RED_HEAD_DUCK_H
#define RED_HEAD_DUCK_H

#include "duck.h"

class Red_Head_Duck : public Duck
{
public:
    Red_Head_Duck();
    virtual ~Red_Head_Duck();
    
    virtual void display();
};

#endif /* RED_HEAD_DUCK_H */

