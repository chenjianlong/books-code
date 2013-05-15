/*!
 * \file winner_state.h
 * \brief The Winner_State class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-15
 */
/* $Id$ */

#ifndef WINNER_STATE_H
#define WINNER_STATE_H

#include <string>
#include "state.h"

class Gumball_Machine;

class Winner_State : public State
{
public:
	Winner_State(Gumball_Machine *machine);
	virtual ~Winner_State();

	virtual void insert_quarter();
	virtual void eject_quarter();
	virtual void turn_crank();
	virtual void dispense();
	virtual std::string to_string();

protected:
	Gumball_Machine *gumball_machine_;
};

#endif /* WINNER_STATE_H */

