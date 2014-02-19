/*!
 * \file gumball_machine.h
 * \brief The Gumball_Machine class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-14
 */
/* $Id$ */

#ifndef GUMBALL_MACHINE_H
#define GUMBALL_MACHINE_H

#include <memory>
#include <string>

class State;

class Gumball_Machine
{
public:
	Gumball_Machine(std::string location, int number_gumballs);
	virtual ~Gumball_Machine();

	virtual void insert_quarter();
	virtual void eject_quarter();
	virtual void turn_crank();
	virtual std::string to_string();
	virtual void set_state(State *state);
	virtual State* get_state();
	virtual State* get_sold_out_state();
	virtual State* get_no_quarter_state();
	virtual State* get_has_quarter_state();
	virtual State* get_sold_state();
	virtual State* get_winner_state();
	virtual void release_ball();
	virtual int get_count();
	virtual std::string get_location();
	virtual void refill(int count);

protected:
	std::auto_ptr<State> sold_out_state_;
	std::auto_ptr<State> no_quarter_state_;
	std::auto_ptr<State> has_quarter_state_;
	std::auto_ptr<State> sold_state_;
	std::auto_ptr<State> winner_state_;
	State *state_;
	int count_;
	std::string location_;
};

#endif /* GUMBALL_MACHINE_H */

