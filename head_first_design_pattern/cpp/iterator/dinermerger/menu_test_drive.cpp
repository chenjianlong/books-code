/* $Id$ */

#include <iostream>
#include "menu_test_drive.h"
#include "waitress.h"
#include "pancake_house_menu.h"
#include "diner_menu.h"

using std::cout;
using std::endl;

Menu_Test_Drive::Menu_Test_Drive()
{ }

Menu_Test_Drive::~Menu_Test_Drive()
{ }

int Menu_Test_Drive::main(int argc, char *argv[])
{
	Pancake_House_Menu pancake_menu;
	Diner_Menu diner_menu;
	Waitress waitress(pancake_menu, diner_menu);
	waitress.print_menu();

	return 0;
}

