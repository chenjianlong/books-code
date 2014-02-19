/* $Id$ */

#include <iostream>
#include <string>
#include "tuner.h"

using std::cout;
using std::endl;
using std::string;

Tuner::Tuner(string description, Amplifier *amplifier) : description_(description), amplifier_(amplifier)
{ }

Tuner::~Tuner()
{ }

void Tuner::on()
{
	cout << description_ << " on" << endl;
}

void Tuner::off()
{
	cout << description_ << " off" << endl;
}

void Tuner::set_frequency(double frequency)
{
	cout << description_ << " setting frequency to " << frequency_ << endl;
	frequency_ = frequency;
}

void Tuner::set_AM()
{
	cout << description_ << " setting AM mode" << endl;
}

void Tuner::set_FM()
{
	cout << description_ << " setting FM mode" << endl;
}

string Tuner::to_string()
{
	return description_;
}

