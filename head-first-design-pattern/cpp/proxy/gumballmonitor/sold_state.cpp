/* $Id$ */

#include <iostream>
#include <string>
#include "sold_state.h"
#include "gumball_machine.h"

using std::cout;
using std::endl;
using std::string;

Sold_State::Sold_State(Gumball_Machine *machine) : gumball_machine_(machine)
{ }

Sold_State::~Sold_State()
{ }

void Sold_State::insert_quarter()
{
	cout << "Please wait, we're already giving you gumball" << endl;
}

void Sold_State::eject_quarter()
{
	cout << "Sorry, you already turned the crank" << endl;
}

void Sold_State::turn_crank()
{
	cout << "Turning twice doesn't get you another gumball" << endl;
}

void Sold_State::dispense()
{
	gumball_machine_->release_ball();
	if (gumball_machine_->get_count() > 0) {
		gumball_machine_->set_state(gumball_machine_->get_no_quarter_state());
	} else {
		cout << "Oops, out of gumballs!" << endl;
		gumball_machine_->set_state(gumball_machine_->get_sold_out_state());
	}
}

string Sold_State::to_string()
{
	return "dispensing a gumball";
}

