/*!
 * \file wild_turkey.h
 * \brief The Wild_Turkey class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef WILD_TURKEY_H
#define WILD_TURKEY_H

#include "turkey.h"

class Wild_Turkey : public Turkey
{
public:
	Wild_Turkey();
	virtual ~Wild_Turkey();

	virtual void gobble();
	virtual void fly();

};

#endif /* WILD_TURKEY_H */

