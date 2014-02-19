/*!
 * \file coffee.h
 * \brief The Coffee class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef COFFEE_H
#define COFFEE_H

class Coffee
{
public:
	Coffee();
	virtual ~Coffee();

	virtual void prepare_recipe();
	virtual void boil_water();
	virtual void brew_coffee_grinds();
	virtual void pour_in_cup();
	virtual void add_sugar_and_milk();
};

#endif /* COFFEE_H */

