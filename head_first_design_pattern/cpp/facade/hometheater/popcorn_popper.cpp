/* $Id$ */

#include <iostream>
#include <string>
#include "popcorn_popper.h"

using std::cout;
using std::endl;
using std::string;

Popcorn_Popper::Popcorn_Popper(string description) : description_(description)
{ }

Popcorn_Popper::~Popcorn_Popper()
{ }

void Popcorn_Popper::on()
{
	cout << description_ << " on" << endl;
}

void Popcorn_Popper::off()
{
	cout << description_ << " off" << endl;
}

void Popcorn_Popper::pop()
{
	cout << description_ << " poping popcorn!" << endl;
}

std::string Popcorn_Popper::to_string()
{
	return description_;
}

