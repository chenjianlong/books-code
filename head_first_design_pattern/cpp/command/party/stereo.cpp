/* $Id$ */

#include <iostream>
#include "stereo.h"

using std::cout;
using std::endl;

Stereo::Stereo(std::string location) : location_(location)
{ }

Stereo::~Stereo()
{ }

void Stereo::on()
{
	cout << location_ << " stereo is on" << endl;
}

void Stereo::off()
{
	cout << location_ << " stereo is off" << endl;
}

void Stereo::set_CD()
{
	cout << location_ << " stereo is set for CD input" << endl;
}

void Stereo::set_DVD()
{
	cout << location_ << " stereo is set for DVD input" << endl;
}

void Stereo::set_radio()
{
	cout << location_ << " stereo is set for radio input" << endl;
}

void Stereo::set_volume(int volume)
{
	cout << location_ << " stereo volume set to " << volume << endl;
}

