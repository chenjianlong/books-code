/* $Id$ */

#include <iostream>
#include <string>
#include "menu.h"

using std::cout;
using std::endl;
using std::string;
using boost::shared_ptr;

Menu::Menu(string name, string description) : name_(name), description_(description)
{ }

Menu::~Menu()
{ }

void Menu::add(Menu_Component *t)
{
	menus_.push_back(MENU(t));
}

void Menu::remove(int i)
{
	menus_.erase(menus_.begin() + i);
}

Menu_Component* Menu::get_child(int i)
{
	return menus_[i].get();
}

string Menu::get_name()
{
	return name_;
}

string Menu::get_description()
{
	return description_;
}

void Menu::print()
{
	cout << "\n" << get_name()
		<< ", " << get_description() << "\n"
		<< "---------------------" << endl;

	for (MENU_LIST::iterator it = menus_.begin(); it != menus_.end(); it++) {
		(*it)->print();
	}
}

