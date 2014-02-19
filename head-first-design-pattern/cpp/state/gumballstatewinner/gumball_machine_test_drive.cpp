/* $Id$ */

#include <iostream>
#include "gumball_machine_test_drive.h"
#include "gumball_machine.h"

using std::cout;
using std::endl;

Gumball_Machine_Test_Drive::Gumball_Machine_Test_Drive()
{ }

Gumball_Machine_Test_Drive::~Gumball_Machine_Test_Drive()
{ }

int Gumball_Machine_Test_Drive::main(int argc, char *argv[])
{
	Gumball_Machine gumball_machine(10);

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

	return 0;
}

