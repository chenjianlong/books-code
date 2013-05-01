/* $Id$ */

#include <iostream>
#include "pizza.h"

using namespace std;

Pizza::Pizza()
{ }

Pizza::~Pizza()
{ }

void Pizza::prepare()
{
	cout << "Preparing " << name_ << endl;
}

void Pizza::bake()
{
	cout << "Baking " << name_ << endl;
}

void Pizza::cut()
{
	cout << "Cutting " << name_ << endl;
}

void Pizza::box()
{
	cout << "Boxing " << name_ << endl;
}

string Pizza::get_name()
{
	return name_;
}

string Pizza::to_string()
{
	string display;
	display = "---- " + name_ + " ----\n";
	display += dough_ + "\n";
	display += sauce_ + "\n";
	for (vector<string>::iterator it = toppings_.begin(); it != toppings_.end(); it++) {
		display += *it;
	}
	return display;
}

