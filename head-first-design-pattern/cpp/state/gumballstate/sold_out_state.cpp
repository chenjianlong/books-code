/* $Id$ */

#include <iostream>
#include <string>
#include "sold_out_state.h"
#include "gumball_machine.h"

using std::cout;
using std::endl;
using std::string;

Sold_Out_State::Sold_Out_State(Gumball_Machine *machine) : gumball_machine_(machine)
{ }

Sold_Out_State::~Sold_Out_State()
{ }

void Sold_Out_State::insert_quarter()
{
	cout << "You can't insert a quarter, the machine is sold out" << endl;
}

void Sold_Out_State::eject_quarter()
{
	cout << "You can't eject, you have't inserted a quarter yet" << endl;
}

void Sold_Out_State::turn_crank()
{
	cout << "You turned, but there are no gumballs" << endl;
}

void Sold_Out_State::dispense()
{
	cout << "No gumball dispensed" << endl;
}

string Sold_Out_State::to_string()
{
	return "sold out";
}

