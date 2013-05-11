/*!
 * \file projector.h
 * \brief The Projector class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef PROJECTOR_H
#define PROJECTOR_H

#include <string>

class DVD_Player;

class Projector
{
public:
	Projector(std::string description, DVD_Player *dvd);
	virtual ~Projector();

	virtual void on();
	virtual void off();
	virtual void wide_screen_mode();
	virtual void TV_mode();
	virtual std::string to_string();

protected:
	std::string description_;
	DVD_Player *dvd_;
};

#endif /* PROJECTOR_H */

