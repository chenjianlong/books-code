/*!
 * \file sold_state.h
 * \brief The Sold_State class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-14
 */
/* $Id$ */

#ifndef SOLD_STATE_H
#define SOLD_STATE_H

#include <string>
#include "state.h"

class Gumball_Machine;

class Sold_State : public State
{
public:
	Sold_State(Gumball_Machine *machine);
	virtual ~Sold_State();

	virtual void insert_quarter();
	virtual void eject_quarter();
	virtual void turn_crank();
	virtual void dispense();
	virtual std::string to_string();

protected:
	Gumball_Machine *gumball_machine_;
};

#endif /* SOLD_STATE_H */

