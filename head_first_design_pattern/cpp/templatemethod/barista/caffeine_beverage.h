/*!
 * \file caffeine_beverage.h
 * \brief The Caffeine_Beverage class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef CAFFEINE_BEVERAGE_H
#define CAFFEINE_BEVERAGE_H

class Caffeine_Beverage
{
public:
	Caffeine_Beverage();
	virtual ~Caffeine_Beverage();

	void prepare_recipe();
	virtual void brew() = 0;
	virtual void add_condiments() = 0;
	virtual void boil_water();
	virtual void pour_in_cup();
};

#endif /* CAFFEINE_BEVERAGE_H */

