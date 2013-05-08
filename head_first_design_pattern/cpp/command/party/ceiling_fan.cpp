/* $Id$ */

#include <iostream>
#include "ceiling_fan.h"

using std::cout;
using std::endl;

Ceiling_Fan::Ceiling_Fan(std::string location) : location_(location), speed_(OFF)
{ }

Ceiling_Fan::~Ceiling_Fan()
{ }

void Ceiling_Fan::high()
{
	speed_ = HIGH;
	cout << location_ << " ceiling fan is on high" << endl;
}

void Ceiling_Fan::medium()
{
	speed_ = MEDIUM;
	cout << location_ << " ceiling fan is on medium" << endl;
}

void Ceiling_Fan::low()
{
	speed_ = LOW;
	cout << location_ << " ceiling fan is on low" << endl;
}

void Ceiling_Fan::off()
{
	speed_ = OFF;
	cout << location_ << " ceiling fan is on off" << endl;
}

int Ceiling_Fan::get_speed()
{
	return speed_;
}

