/* $Id$ */

#include <iostream>
#include "pizza.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

Pizza::Pizza()
{ }

Pizza::~Pizza()
{ }

void Pizza::prepare()
{
	cout << "Preparing " << name_ << endl;
	cout << "Tossing dough..." << endl;
	cout << "Adding sauce..." << endl;
	cout << "Adding toppings: " << endl;
	for (vector<string>::iterator it = toppings_.begin(); it != toppings_.end(); it++) {
		cout << "    " << *it << endl;
	}
}

void Pizza::bake()
{
	cout << "Bake for 25 minutes to 350" << endl;
}

void Pizza::cut()
{
	cout << "Cutting the pizza into diagonal slices" << endl;
}

void Pizza::box()
{
	cout << "Place pizza in official PizzaStore box" << endl;
}

string Pizza::get_name()
{
	return name_;
}

string Pizza::to_string()
{
	string display;
	display = "----" + name_ + "----\n";
	display += dough_ + "\n";
	display += sauce_ + "\n";
	for (vector<string>::iterator it = toppings_.begin(); it != toppings_.end(); it++) {
		display += *it + "\n";
	}
	return display;
}

