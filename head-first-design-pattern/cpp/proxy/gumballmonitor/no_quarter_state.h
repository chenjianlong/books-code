/*!
 * \file no_quarter_state.h
 * \brief The No_Quarter_State class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-14
 */
/* $Id$ */

#ifndef NO_QUARTER_STATE_H
#define NO_QUARTER_STATE_H

#include <string>
#include "state.h"

class Gumball_Machine;

class No_Quarter_State : public State
{
public:
	No_Quarter_State(Gumball_Machine *machine);
	virtual ~No_Quarter_State();

	virtual void insert_quarter();
	virtual void eject_quarter();
	virtual void turn_crank();
	virtual void dispense();
	virtual std::string to_string();

protected:
	Gumball_Machine *gumball_machine_;
};

#endif /* NO_QUARTER_STATE_H */

