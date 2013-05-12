/*!
 * \file caffeiner_beverage_with_hook.h
 * \brief The Caffeiner_Beverage_With_Hook class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef CAFFEINER_BEVERAGE_WITH_HOOK_H
#define CAFFEINER_BEVERAGE_WITH_HOOK_H

class Caffeiner_Beverage_With_Hook
{
public:
	Caffeiner_Beverage_With_Hook();
	virtual ~Caffeiner_Beverage_With_Hook();

	virtual void prepare_recipe();
	virtual void brew() = 0;
	virtual void add_condiments() = 0;
	virtual void boil_water();
	virtual void pour_in_cup();
	virtual bool customer_wants_condiments();

};

#endif /* CAFFEINER_BEVERAGE_WITH_HOOK_H */

