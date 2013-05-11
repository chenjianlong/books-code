/*!
 * \file home_theater_facade.h
 * \brief The Home_Theater_Facade class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef HOME_THEATER_FACADE_H
#define HOME_THEATER_FACADE_H

#include <string>

class Amplifier;
class Tuner;
class DVD_Player;
class CD_Player;
class Projector;
class Theater_Lights;
class Screen;
class Popcorn_Popper;

class Home_Theater_Facade
{
public:
	Home_Theater_Facade(Amplifier *amp,
			Tuner *tuner,
			DVD_Player *dvd,
			CD_Player *cd,
			Projector *projector,
			Screen *screen,
			Theater_Lights *lights,
			Popcorn_Popper *popper);
	virtual ~Home_Theater_Facade();

	virtual void watch_movie(std::string movie);
	virtual void end_movie();
	virtual void listen_to_CD(std::string cd_title);
	virtual void end_CD();
	virtual void listen_to_radio(double frequency);
	virtual void end_radio();

protected:
	Amplifier *amp_;
	Tuner *tuner_;
	DVD_Player *dvd_;
	CD_Player *cd_;
	Projector *projector_;
	Theater_Lights *lights_;
	Screen *screen_;
	Popcorn_Popper *popper_;
};

#endif /* HOME_THEATER_FACADE_H */

