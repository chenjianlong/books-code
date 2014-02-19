/* $Id$ */

#include <iostream>
#include <string>
#include "cd_player.h"

using std::cout;
using std::endl;
using std::string;

CD_Player::CD_Player(string description, Amplifier *amplifier)
{ }

CD_Player::~CD_Player()
{ }

void CD_Player::on()
{
	cout << description_ << " on" << endl;
}

void CD_Player::off()
{
	cout << description_ << " off" << endl;
}

void CD_Player::eject()
{
	title_.clear();
	current_track_ = 0;
	cout << description_ << " eject" << endl;
}

void CD_Player::play(string title)
{
	title_ = title;
	current_track_ = 0;
	cout << description_ << " playing\"" << title << "\"" << endl;
}

void CD_Player::play(int track)
{
	if (title_.empty()) {
		cout << description_ << " can't play track " << current_track_ << ", no CD inserted" << endl;
	} else {
		current_track_ = track;
		cout << description_ << " playing track " << current_track_ << endl;
	}
}

void CD_Player::stop()
{
	current_track_ = 0;
	cout << description_ << " stopped" << endl;
}

void CD_Player::pause()
{
	cout << description_ << " paused \"" << title_ << "\"" << endl;
}

std::string CD_Player::to_string()
{
	return description_;
}

