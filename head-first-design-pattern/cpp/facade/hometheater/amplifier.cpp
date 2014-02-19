/* $Id$ */

#include <iostream>
#include <string>
#include "amplifier.h"
#include "tuner.h"
#include "dvd_player.h"
#include "cd_player.h"

using std::cout;
using std::endl;
using std::string;

Amplifier::Amplifier(string description) : description_(description)
{ }

Amplifier::~Amplifier()
{ }

void Amplifier::on()
{
	cout << description_ << " on" << endl;
}

void Amplifier::off()
{
	cout << description_ << " off" << endl;
}

void Amplifier::set_stereo_sound()
{
	cout << description_ << " stereo mode on" << endl;
}

void Amplifier::set_surround_sound()
{
	cout << description_ << " surround sound on (t speakers, 1 subwoofer)" << endl;
}

void Amplifier::set_volume(int level)
{
	cout << description_ << " setting volume to " << level << endl;
}

void Amplifier::set_tuner(Tuner *tuner)
{
	cout << description_ << " setting tuner to " << tuner->to_string() << endl;
	tuner_ = tuner;
}

void Amplifier::set_DVD(DVD_Player *dvd)
{
	cout << description_ << " setting DVD player to " << dvd->to_string() << endl;
	dvd_ = dvd;
}

void Amplifier::set_CD(CD_Player *cd)
{
	cout << description_ << " setting CD player to " << cd->to_string() << endl;
	cd_ = cd;
}

string Amplifier::to_string()
{
	return description_;
}

