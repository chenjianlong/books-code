/* $Id$ */

#include <iostream>
#include "hottub.h"

using std::cout;
using std::endl;

Hottub::Hottub() : on_(false), temperature_(0)
{ }

Hottub::~Hottub()
{ }

void Hottub::on()
{
	on_ = true;
}

void Hottub::off()
{
	on_ = false;
}

void Hottub::circulate()
{
	if (on_) {
		cout << "Hottub is bubbing!" << endl;
	}
}

void Hottub::jets_on()
{
	if (on_) {
		cout << "Hottub jets are on" << endl;
	}
}

void Hottub::jets_off()
{
	if (on_) {
		cout << "Huttub jets are off" << endl;
	}
}

void Hottub::set_temperature(int temperature)
{
	if (temperature > temperature_) {
		cout << "Hottub is heating to a steaming " << temperature << " degrees" << endl;
	} else {
		cout << "Hottub is cooling to " << temperature << " degrees" << endl;
	}
	temperature_ = temperature;
}

