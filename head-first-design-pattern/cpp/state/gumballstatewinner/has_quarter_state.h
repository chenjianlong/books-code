/*!
 * \file has_quarter_state.h
 * \brief The Has_Quarter_State class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-14
 */
/* $Id$ */

#ifndef HAS_QUARTER_STATE_H
#define HAS_QUARTER_STATE_H

#include <string>
#include "state.h"

class Gumball_Machine;

class Has_Quarter_State : public State
{
public:
	Has_Quarter_State(Gumball_Machine *gumball_machine);
	virtual ~Has_Quarter_State();

	virtual void insert_quarter();
	virtual void eject_quarter();
	virtual void turn_crank();
	virtual void dispense();
	virtual std::string to_string();

protected:
	Gumball_Machine *gumball_machine_;
};

#endif /* HAS_QUARTER_STATE_H */

