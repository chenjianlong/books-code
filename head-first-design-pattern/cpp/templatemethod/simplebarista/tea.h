/*!
 * \file tea.h
 * \brief The Tea class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef TEA_H
#define TEA_H

class Tea
{
public:
	Tea();
	virtual ~Tea();

	virtual void prepare_recipe();
	virtual void boil_water();
	virtual void steep_tea_bag();
	virtual void pour_in_cup();
	virtual void add_lemon();
};

#endif /* TEA_H */

