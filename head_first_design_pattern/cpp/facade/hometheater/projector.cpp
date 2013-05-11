/* $Id$ */

#include <iostream>
#include <string>
#include "projector.h"

using std::cout;
using std::endl;
using std::string;

Projector::Projector(string description, DVD_Player *dvd) : description_(description), dvd_(dvd)
{ }

Projector::~Projector()
{ }

void Projector::on()
{
	cout << description_ << " on" << endl;
}

void Projector::off()
{
	cout << description_ << " off" << endl;
}

void Projector::wide_screen_mode()
{
	cout << description_ << " in wide sreen mode (16x9 aspect ratio)" << endl;
}

void Projector::TV_mode()
{
	cout << description_ << " in TV mode (4x3 aspect ratio)" << endl;
}

string Projector::to_string()
{
	return description_;
}

