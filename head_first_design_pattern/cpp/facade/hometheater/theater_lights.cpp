/* $Id$ */

#include <iostream>
#include <string>
#include "theater_lights.h"

using std::cout;
using std::endl;
using std::string;

Theater_Lights::Theater_Lights(string description) : description_(description)
{ }

Theater_Lights::~Theater_Lights()
{ }

void Theater_Lights::on()
{
	cout << description_ << " on" << endl;
}

void Theater_Lights::off()
{
	cout << description_ << " off" << endl;
}

void Theater_Lights::dim(int level)
{
	cout << description_ << " dimming to " << level << "%" << endl;
}

string Theater_Lights::to_string()
{
	return description_;
}

