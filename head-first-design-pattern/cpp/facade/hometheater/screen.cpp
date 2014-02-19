/* $Id$ */

#include <iostream>
#include "screen.h"

using std::cout;
using std::endl;

Screen::Screen(std::string description) : description_(description)
{ }

Screen::~Screen()
{ }

void Screen::up()
{
	cout << description_ << " going up" << endl;
}

void Screen::down()
{
	cout << description_ << "goint down" << endl;
}

std::string Screen::to_string()
{
	return description_;
}

