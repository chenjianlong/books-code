/* $Id$ */

#include <string>
#include <iostream>
#include "no_quarter_state.h"
#include "gumball_machine.h"

using std::cout;
using std::endl;
using std::string;

No_Quarter_State::No_Quarter_State(Gumball_Machine *machine) : gumball_machine_(machine)
{ }

No_Quarter_State::~No_Quarter_State()
{ }

void No_Quarter_State::insert_quarter()
{
	cout << "You inserted a quarter" << endl;
	gumball_machine_->set_state(gumball_machine_->get_has_quarter_state());
}

void No_Quarter_State::eject_quarter()
{
	cout << "You haven't inserted a quarter" << endl;
}

void No_Quarter_State::turn_crank()
{
	cout << "You turned, but there's no quarter" << endl;
}

void No_Quarter_State::dispense()
{
	cout << "You need to pay first" << endl;
}

string No_Quarter_State::to_string()
{
	return "waiting for quarter";
}

