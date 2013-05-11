/* $Id$ */

#include <iostream>
#include <string>
#include "dvd_player.h"

using std::cout;
using std::endl;
using std::string;

DVD_Player::DVD_Player(string description, Amplifier *amplifier) : description_(description), amplifier_(amplifier)
{ }

DVD_Player::~DVD_Player()
{ }

void DVD_Player::on()
{
	cout << description_ << " on" << endl;
}

void DVD_Player::off()
{
	cout << description_ << " off" << endl;
}

void DVD_Player::eject()
{
	movie_.clear();
	cout << description_ << " eject" << endl;
}

void DVD_Player::play(string movie)
{
	movie_ = movie;
	current_track_ = 0;
	cout << description_ << " playing \"" << movie_ << "\"" << endl;
}

void DVD_Player::play(int track)
{
	if (movie_.empty()) {
		cout << description_ << " can't play track" << track << " no DVD inserted" << endl;
	} else {
		current_track_ = track;
		cout << description_ << " playing track " << current_track_ << " of \"" << movie_ << "\"" << endl;
	}
}

void DVD_Player::stop()
{
	current_track_ = 0;
	cout << description_ << " stopped \"" << movie_ << "\"" << endl;
}

void DVD_Player::pause()
{
	cout << description_ << " paused \"" << movie_ << "\"" << endl;
}

void DVD_Player::set_two_channel_audio()
{
	cout << description_ << " set two channel audio" << endl;
}

void DVD_Player::set_surround_audio()
{
	cout << description_ << " set surround audio" << endl;
}

string DVD_Player::to_string()
{
	return description_;
}

