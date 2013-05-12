/*!
 * \file tea_with_hook.h
 * \brief The Tea_With_Hook class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef TEA_WITH_HOOK_H
#define TEA_WITH_HOOK_H

#include <string>
#include "caffeiner_beverage_with_hook.h"

class Tea_With_Hook : public Caffeiner_Beverage_With_Hook
{
public:
	Tea_With_Hook();
	virtual ~Tea_With_Hook();

	virtual void brew();
	virtual void add_condiments();
	virtual bool customer_wants_condiments();

private:
	std::string get_user_input();
};

#endif /* TEA_WITH_HOOK_H */

