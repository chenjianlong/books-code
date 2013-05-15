/* $Id$ */

#include <iostream>
#include "gumball_monitor.h"
#include "gumball_machine.h"
#include "state.h"

using std::cout;
using std::endl;

Gumball_Monitor::Gumball_Monitor(Gumball_Machine &machine) : machine_(machine)
{ }

Gumball_Monitor::~Gumball_Monitor()
{ }

void Gumball_Monitor::report()
{
	cout << "Gumball Machine: " << machine_.get_location() << "\n"
		<< "Current inventory: " << machine_.get_count() << " gumballs\n"
		<< "Current state: " << machine_.get_state()->to_string() << endl;
}

