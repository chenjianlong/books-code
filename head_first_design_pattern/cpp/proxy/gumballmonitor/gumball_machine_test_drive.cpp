/* $Id$ */

#include <iostream>
#include <cstdlib>
#include "gumball_machine_test_drive.h"
#include "gumball_machine.h"
#include "gumball_monitor.h"

using std::cout;
using std::endl;

Gumball_Machine_Test_Drive::Gumball_Machine_Test_Drive()
{ }

Gumball_Machine_Test_Drive::~Gumball_Machine_Test_Drive()
{ }

int Gumball_Machine_Test_Drive::main(int argc, char *argv[])
{
	if (argc < 3) {
		cout << argv[0] << " <name> <inventory>" << endl;
		return 1;
	}

	Gumball_Machine gumball_machine(argv[1], atoi(argv[2]));
	Gumball_Monitor monitor(gumball_machine);

	cout << gumball_machine.to_string() << endl;

	gumball_machine.insert_quarter();
	gumball_machine.turn_crank();
	gumball_machine.insert_quarter();
	gumball_machine.turn_crank();

	cout << gumball_machine.to_string() << endl;

	gumball_machine.insert_quarter();
	gumball_machine.turn_crank();
	gumball_machine.insert_quarter();
	gumball_machine.turn_crank();

	cout << gumball_machine.to_string() << endl;

	gumball_machine.insert_quarter();
	gumball_machine.turn_crank();
	gumball_machine.insert_quarter();
	gumball_machine.turn_crank();

	cout << gumball_machine.to_string() << endl;

	gumball_machine.insert_quarter();
	gumball_machine.turn_crank();
	gumball_machine.insert_quarter();
	gumball_machine.turn_crank();

	cout << gumball_machine.to_string() << endl;

	gumball_machine.insert_quarter();
	gumball_machine.turn_crank();
	gumball_machine.insert_quarter();
	gumball_machine.turn_crank();

	cout << gumball_machine.to_string() << endl;

	monitor.report();

	return 0;
}

