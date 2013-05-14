/* $Id$ */

#include <sstream>
#include <iostream>
#include <string>
#include "gumball_machine.h"
#include "sold_out_state.h"
#include "no_quarter_state.h"
#include "has_quarter_state.h"
#include "sold_state.h"
#include "winner_state.h"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

Gumball_Machine::Gumball_Machine(int number_gumballs) : count_(number_gumballs)
{ 
	sold_out_state_.reset(new Sold_Out_State(this));
	no_quarter_state_.reset(new No_Quarter_State(this));
	has_quarter_state_.reset(new Has_Quarter_State(this));
	sold_state_.reset(new Sold_State(this));
	winner_state_.reset(new Winner_State(this));
	if (number_gumballs > 0) {
		state_ = no_quarter_state_.get();
	} else {
		state_ = sold_out_state_.get();
	}
}

Gumball_Machine::~Gumball_Machine()
{ }

void Gumball_Machine::insert_quarter()
{
	state_->insert_quarter();
}

void Gumball_Machine::eject_quarter()
{
	state_->eject_quarter();
}

void Gumball_Machine::turn_crank()
{
	state_->turn_crank();
	state_->dispense();
}

void Gumball_Machine::set_state(State *state)
{
	state_ = state;
}

void Gumball_Machine::release_ball()
{
	cout << "A gumball comes rolling out the solt..." << endl;
	if (count_) {
		count_--;
	}
}

int Gumball_Machine::get_count()
{
	return count_;
}

void Gumball_Machine::refill(int count)
{
	count_ = count;
	if (count) {
		state_ = no_quarter_state_.get();
	} else {
		state_ = sold_out_state_.get();
	}
}

State* Gumball_Machine::get_state()
{
	return state_;
}

State* Gumball_Machine::get_sold_out_state()
{
	return sold_out_state_.get();
}

State* Gumball_Machine::get_no_quarter_state()
{
	return no_quarter_state_.get();
}

State* Gumball_Machine::get_has_quarter_state()
{
	return has_quarter_state_.get();
}

State* Gumball_Machine::get_sold_state()
{
	return sold_state_.get();
}

State* Gumball_Machine::get_winner_state()
{
	return winner_state_.get();
}

string Gumball_Machine::to_string()
{
	stringstream result;
	result << "\nMighty Gumball, Inc.";
	result << "\nJava-enabled Standing Gumball Model #2004\n";
	result << "Inventory: " << count_ << " gumball";
	if (count_ > 1) {
		result << "s";
	}
	result << "\nMachine is " << state_->to_string() << "\n";
	return result.str();
}

