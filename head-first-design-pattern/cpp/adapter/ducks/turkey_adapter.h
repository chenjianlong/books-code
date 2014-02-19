/*!
 * \file turkey_adapter.h
 * \brief The Turkey_Adapter class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef TURKEY_ADAPTER_H
#define TURKEY_ADAPTER_H

#include "duck.h"

class Turkey;

class Turkey_Adapter : public Duck
{
public:
	Turkey_Adapter(Turkey *turkey);
	virtual ~Turkey_Adapter();

	virtual void quack();
	virtual void fly();

protected:
	Turkey *turkey_;
};

#endif /* TURKEY_ADAPTER_H */

