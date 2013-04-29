/*!
 * \file model_duck.h
 * \brief The Model_Duck class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-29
 */
/* $Id$ */

#ifndef MODEL_DUCK_H
#define MODEL_DUCK_H

#include "duck.h"

class Model_Duck : public Duck
{
public:
    Model_Duck();
    virtual ~Model_Duck();

    virtual void display();
};

#endif /* MODEL_DUCK_H */

