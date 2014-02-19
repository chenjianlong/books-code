/* $Id$ */

#include <iostream>
#include <string>
#include "menu_item.h"

using std::cout;
using std::endl;
using std::string;

Menu_Item::Menu_Item(string name,
		string description, 
		bool vegetarian,
		double price) : name_(name), description_(description), vegetarian_(vegetarian), price_(price)
{ }

Menu_Item::~Menu_Item()
{ }

string Menu_Item::get_name()
{
	return name_;
}

string Menu_Item::get_description()
{
	return description_;
}

double Menu_Item::get_price()
{
	return price_;
}

bool Menu_Item::is_vegetarian()
{
	return vegetarian_;
}

void Menu_Item::print()
{
	cout << "  " << get_name();
	if (is_vegetarian()) {
		cout << "(v)";
	}
	cout << ", " << get_price() << "\n"
		<< "    -- " << get_description() << endl;
}

