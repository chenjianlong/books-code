/* $Id$ */

#include <string>
#include <stdexcept>
#include "menu_component.h"

using std::string;
using std::runtime_error;

Menu_Component::Menu_Component()
{ }

Menu_Component::~Menu_Component()
{ }

void Menu_Component::add(Menu_Component *t)
{
	throw runtime_error("Unsupported Operation");
}

void Menu_Component::remove(int i)
{
	throw runtime_error("Unsupported Operation");
}

Menu_Component* Menu_Component::get_child(int i)
{
	throw runtime_error("Unsupported Operation");
}

string Menu_Component::get_name()
{
	throw runtime_error("Unsupported Operation");
}

string Menu_Component::get_description()
{
	throw runtime_error("Unsupported Operation");
}

double Menu_Component::get_price()
{
	throw runtime_error("Unsupported Operation");
}

bool Menu_Component::is_vegetarian()
{
	throw runtime_error("Unsupported Operation");
}

void Menu_Component::print()
{
	throw runtime_error("Unsupported Operation");
}

