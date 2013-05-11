/*!
 * \file amplifier.h
 * \brief The Amplifier class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef AMPLIFIER_H
#define AMPLIFIER_H

#include <string>

class Tuner;
class DVD_Player;
class CD_Player;

class Amplifier
{
public:
	Amplifier(std::string description);
	virtual ~Amplifier();

	virtual void on();
	virtual void off();
	virtual void set_stereo_sound();
	virtual void set_surround_sound();
	virtual void set_volume(int level);
	virtual void set_tuner(Tuner *tuner);
	virtual void set_DVD(DVD_Player *dvd);
	virtual void set_CD(CD_Player *cd);
	virtual std::string to_string();

protected:
	std::string description_;
	Tuner *tuner_;
	DVD_Player *dvd_;
	CD_Player *cd_;
};

#endif /* AMPLIFIER_H */

