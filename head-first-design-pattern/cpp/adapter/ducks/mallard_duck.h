/*!
 * \file mallard_duck.h
 * \brief The Mallard_Duck class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef MALLARD_DUCK_H
#define MALLARD_DUCK_H

#include "duck.h"

class Mallard_Duck : public Duck
{
public:
	Mallard_Duck();
	virtual ~Mallard_Duck();

	virtual void quack();
	virtual void fly();
};

#endif /* MALLARD_DUCK_H */

