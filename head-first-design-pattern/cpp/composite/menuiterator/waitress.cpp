/* $Id$ */

#include <iostream>
#include <stdexcept>
#include "waitress.h"
#include "menu_component.h"
#include "common.h"
#include "iterator.h"

using std::cout;
using std::endl;
using std::runtime_error;

Waitress::Waitress(Menu_Component &all_menus) : all_menus_(all_menus)
{ }

Waitress::~Waitress()
{ }

void Waitress::print_menu()
{
	all_menus_.print();
}

void Waitress::print_vegetarian_menu()
{
	cout << "\nVEGETARIAN MENU\n----" << endl;
	ITER_PTR it(all_menus_.create_iterator());
	Menu_Component *component;
	while (it->has_next()) {
		component = it->next();

		try {
			if (component->is_vegetarian()) {
				component->print();
			}
		} catch (runtime_error) {
		
		}
	}
}

