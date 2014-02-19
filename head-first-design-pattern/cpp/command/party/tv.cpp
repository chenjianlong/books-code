/* $Id$ */

#include <iostream>
#include "tv.h"

using std::cout;
using std::endl;

TV::TV(std::string location) : location_(location), channel_(0)
{ }

TV::~TV()
{ }

void TV::on()
{
	cout << location_ << " TV is on" << endl;
}

void TV::off()
{
	cout << location_ << " TV is off" << endl;
}

void TV::set_input_channel()
{
	channel_ = 3;
	cout << location_ << " TV channel is set for DVD" << endl;
}

