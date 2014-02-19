/* $Id$ */

#include <iostream>
#include "menu_test_drive.h"
#include "waitress.h"
#include "pancake_house_menu.h"
#include "diner_menu.h"
#include "cafe_menu.h"

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
	Cafe_Menu cafe_menu;
	Waitress waitress(pancake_menu, diner_menu, cafe_menu);
	waitress.print_menu();
	waitress.print_vegatarian_menu();

	cout << "\nCustomer asks, is the Hotdoy vegetarian?" << endl;
	cout << "Waitress says: ";
	if (waitress.is_item_vegetarian("Hotdog")) {
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}
	cout << "\nCustomer asks, is the Waffles vegetarian?" << endl;
	cout << "Waitress says: ";
	if (waitress.is_item_vegetarian("Waffles")) {
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}

	return 0;
}

