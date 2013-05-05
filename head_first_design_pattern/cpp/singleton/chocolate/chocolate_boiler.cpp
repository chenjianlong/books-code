/* $Id$ */

#include <iostream>
#include "chocolate_boiler.h"

using std::cout;
using std::endl;

Chocolate_Boiler* Chocolate_Boiler::unique_(NULL);

Chocolate_Boiler::Chocolate_Boiler() : empty_(true), boiled_(false) 
{ }

Chocolate_Boiler::~Chocolate_Boiler()
{ }

Chocolate_Boiler* Chocolate_Boiler::get_instance()
{
	if (!unique_) {
		cout << "Creating unique instance of Chocolate Boilder" << endl;
		unique_ = new Chocolate_Boiler();
	}
	cout << "Returning instance of Chocolate Boilder" << endl;
	return unique_;
}

void Chocolate_Boiler::fill()
{
	if (is_empty()) {
		empty_ = false;
		boiled_ = false;
	}
}

void Chocolate_Boiler::drain()
{
	if (!is_empty() && is_boiled()) {
		empty_ = true;
	}
}

void Chocolate_Boiler::boil()
{
	if (!is_empty() && !is_boiled()) {
		boiled_ = true;
	}
}

bool Chocolate_Boiler::is_empty()
{
	return empty_;
}

bool Chocolate_Boiler::is_boiled()
{
	return boiled_;
}

void Chocolate_Boiler::close()
{
	delete unique_;
	unique_ = NULL;
}
