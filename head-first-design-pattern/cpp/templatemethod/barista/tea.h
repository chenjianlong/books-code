/*!
 * \file tea.h
 * \brief The Tea class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef TEA_H
#define TEA_H

#include "caffeine_beverage.h"

class Tea : public Caffeine_Beverage
{
public:
	Tea();
	virtual ~Tea();

	virtual void brew();
	virtual void add_condiments();
};

#endif /* TEA_H */

