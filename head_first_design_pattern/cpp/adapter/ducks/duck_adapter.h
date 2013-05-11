/*!
 * \file duck_adapter.h
 * \brief The Duck_Adapter class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef DUCK_ADAPTER_H
#define DUCK_ADAPTER_H

#include "turkey.h"

class Duck;

class Duck_Adapter : public Turkey
{
public:
	Duck_Adapter(Duck *duck);
	virtual ~Duck_Adapter();

	virtual void gobble();
	virtual void fly();

protected:
	Duck *duck_;
};

#endif /* DUCK_ADAPTER_H */

