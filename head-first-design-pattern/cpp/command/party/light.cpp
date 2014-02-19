/* $Id$ */

#include <iostream>
#include "light.h"

using std::cout;
using std::endl;

Light::Light(std::string location) : location_(location), level_(0)
{ }

Light::~Light()
{ }

void Light::on()
{
	level_ = 100;
	cout << "Light is on" << endl;
}

void Light::off()
{
	level_ = 0;
	cout << "Light is off" << endl;
}

void Light::dim(int level)
{
	level_ = level;
	if (0 == level) {
		off();
	} else {
		cout << "Light is dimmed to " << level_ << "%" << endl;
	}
}

int Light::get_level()
{
	return level_;
}

