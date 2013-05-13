/* $Id$ */

#include "waitress.h"
#include "menu_component.h"

Waitress::Waitress(Menu_Component &all_menus) : all_menus_(all_menus)
{ }

Waitress::~Waitress()
{ }

void Waitress::print_menu()
{
	all_menus_.print();
}

