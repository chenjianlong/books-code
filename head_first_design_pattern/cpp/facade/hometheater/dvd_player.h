/*!
 * \file dvd_player.h
 * \brief The Dvd_Player class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef DVD_PLAYER_H
#define DVD_PLAYER_H

#include <string>

class Amplifier;

class DVD_Player
{
public:
	DVD_Player(std::string description, Amplifier *amplifier);
	virtual ~DVD_Player();
	
	virtual void on();
	virtual void off();
	virtual void eject();
	virtual void play(std::string movie);
	virtual void play(int track);
	virtual void stop();
	virtual void pause();
	virtual void set_two_channel_audio();
	virtual void set_surround_audio();
	virtual std::string to_string();

protected:
	std::string description_;
	int current_track_;
	Amplifier *amplifier_;
	std::string movie_;
};

#endif /* DVD_PLAYER_H */

