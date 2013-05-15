/* $Id$ */

#include <string>
#include <iostream>
#include <cstdlib>
#include "has_quarter_state.h"
#include "gumball_machine.h"

using std::cout;
using std::endl;
using std::string;

Has_Quarter_State::Has_Quarter_State(Gumball_Machine *gumball_machine) : gumball_machine_(gumball_machine)
{ }

Has_Quarter_State::~Has_Quarter_State()
{ }

void Has_Quarter_State::insert_quarter()
{
	cout << "You can't insert another quarter" << endl;
}

void Has_Quarter_State::eject_quarter()
{
	cout << "Quarter returned" << endl;
	gumball_machine_->set_state(gumball_machine_->get_no_quarter_state());
}

void Has_Quarter_State::turn_crank()
{
	cout << "You turned..." << endl;
	int winner = rand() % 10;
	if ((0 == winner) && gumball_machine_->get_count() > 1) {
		gumball_machine_->set_state(gumball_machine_->get_winner_state());	
	} else {
		gumball_machine_->set_state(gumball_machine_->get_sold_state());
	}
}

void Has_Quarter_State::dispense()
{
	cout << "No gumball dispensed" << endl;
}

string Has_Quarter_State::to_string()
{
	return "waiting for turn of crank";
}

