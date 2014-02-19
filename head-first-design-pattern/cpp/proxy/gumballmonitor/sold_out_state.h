/*!
 * \file sold_out_state.h
 * \brief The Sold_Out_State class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-14
 */
/* $Id$ */

#ifndef SOLD_OUT_STATE_H
#define SOLD_OUT_STATE_H

#include <string>
#include "state.h"

class Gumball_Machine;

class Sold_Out_State : public State
{
public:
	Sold_Out_State(Gumball_Machine *machine);
	virtual ~Sold_Out_State();

	virtual void insert_quarter();
	virtual void eject_quarter();
	virtual void turn_crank();
	virtual void dispense();
	virtual std::string to_string();

protected:
	Gumball_Machine *gumball_machine_;
};

#endif /* SOLD_OUT_STATE_H */

