/* $Id$ */

#include <iostream>
#include <string>
#include "winner_state.h"
#include "gumball_machine.h"

using std::cout;
using std::endl;
using std::string;

Winner_State::Winner_State(Gumball_Machine *machine) : gumball_machine_(machine)
{ }

Winner_State::~Winner_State()
{ }

void Winner_State::insert_quarter()
{
	cout << "Please wait, we're already giving you a Gumball" << endl;
}

void Winner_State::eject_quarter()
{
	cout << "Please wait, we're already giving you a Gumball" << endl;
}

void Winner_State::turn_crank()
{
	cout << "Turning again doesn't get you another gumball" << endl;
}

void Winner_State::dispense()
{
	cout << "YOU'RE A WINNER! You get two gumballs for your quarter" << endl;
	gumball_machine_->release_ball();
	if (!gumball_machine_->get_count()) {
		gumball_machine_->set_state(gumball_machine_->get_sold_out_state());
	} else {
		gumball_machine_->release_ball();
		if (gumball_machine_->get_count()) {
			gumball_machine_->set_state(gumball_machine_->get_no_quarter_state());
		} else {
			cout << "Oops, out of gumballs!" << endl;
			gumball_machine_->set_state(gumball_machine_->get_sold_out_state());
		}
	}
}

string Winner_State::to_string()
{
	return "depensing two gamballs for your quarter, because YOU'RE A WINNER!";
}

