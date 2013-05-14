/* $Id$ */

#include <sstream>
#include <string>
#include <iostream>
#include "gumball_machine.h"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

Gumball_Machine::Gumball_Machine(unsigned int count) : count_(count), state_(SOLD_OUT)
{ 
	if (count_ > 0) {
		state_ = NO_QUARTER;
	}
}

Gumball_Machine::~Gumball_Machine()
{ }

void Gumball_Machine::insert_quarter()
{
	switch (state_) {
	case HAS_QUARTER:
		cout << "You can't insert another quarter" << endl;
		break;
	case NO_QUARTER:
		state_ = HAS_QUARTER;
		cout << "You inserted a quarter" << endl;
		break;
	case SOLD_OUT:
		cout << "You can't insert a quarter, the machine is sold out" << endl;
		break;
	case SOLD:
		cout << "Please wait, we're already giving you a gumball" << endl;
		break;
	default:
		break;
	}
}

void Gumball_Machine::eject_quarter()
{
	switch (state_) {
	case HAS_QUARTER:
		cout << "Quarter returned" << endl;
		state_ = NO_QUARTER;
		break;
	case NO_QUARTER:
		cout << "You haven't inserted a quarter" << endl;
		break;
	case SOLD:
		cout << "Sorry, you already turned the crank" << endl;
		break;
	case SOLD_OUT:
		cout << "You can't eject, you haven't inserted a quarter yet" << endl;
		break;
	default:
		break;
	}
}

void Gumball_Machine::turn_crank()
{
	switch (state_) {
	case SOLD:
		cout << "Turning twice doesn't get you another gumball!" << endl;
		break;
	case NO_QUARTER:
		cout << "You turned but there's no quarter" << endl;
		break;
	case SOLD_OUT:
		cout << "You turned, but there are no gumballs" << endl;
		break;
	case HAS_QUARTER:
		cout << "You turned..." << endl;
		state_ = SOLD;
		dispense();
		break;
	default:
		break;
	}
}

void Gumball_Machine::dispense()
{
	switch (state_) {
	case SOLD:
		cout << "A gumball comes rolling out the slot" << endl;
		if (!(--count_)) {
			cout << "Oops, out of gumballs!" << endl;
			state_ = SOLD_OUT;
		} else {
			state_ = NO_QUARTER;
		}
		break;
	case NO_QUARTER:
		cout << "You need a pay first" << endl;
		break;
	case SOLD_OUT:
		cout << "No gumball dispensed" << endl;
		break;
	case HAS_QUARTER:
		cout << "No gumball dispensed" << endl;
		break;
	default:
		break;
	}
}

void Gumball_Machine::refill(unsigned int num)
{
	count_ = num;
	state_ = NO_QUARTER;
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
	result << "\nMachine is ";
	switch (state_) {
	case SOLD_OUT:
		result << "sold out";
		break;
	case NO_QUARTER:
		result << "waiting for quarter";
		break;
	case HAS_QUARTER:
		result << "waiting for turn of crank";
		break;
	case SOLD:
		result << "delivering a gumball";
	default:
		break;
	}
	result << "\n";
	return result.str();
}

