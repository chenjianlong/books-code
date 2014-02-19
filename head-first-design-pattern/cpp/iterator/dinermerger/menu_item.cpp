/* $Id$ */

#include <sstream>
#include <string>
#include "menu_item.h"

using std::stringstream;
using std::string;

Menu_Item::Menu_Item() : vegetarian_(false), price_(0)
{ }

Menu_Item::Menu_Item(
		string name,
		string description,
		bool vegetarian,
		double price
		) : name_(name), description_(description), vegetarian_(vegetarian), price_(price)
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

string Menu_Item::to_string()
{

	stringstream ss;
	ss << name_ << ", $" << price_ << "\n   " << description_;
	return ss.str();
}

