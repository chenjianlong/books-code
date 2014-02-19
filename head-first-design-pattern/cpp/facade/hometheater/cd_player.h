/*!
 * \file cd_player.h
 * \brief The Cd_Player class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef CD_PLAYER_H
#define CD_PLAYER_H

#include <string>

class Amplifier;

class CD_Player
{
public:
	CD_Player(std::string description, Amplifier *Amplifier);
	virtual ~CD_Player();

	virtual void on();
	virtual void off();
	virtual void eject();
	virtual void play(std::string title);
	virtual void play(int track);
	virtual void stop();
	virtual void pause();
	virtual std::string to_string();

protected:
	std::string description_;
	int current_track_;
	Amplifier *amplifier_;
	std::string title_;
};

#endif /* CD_PLAYER_H */

