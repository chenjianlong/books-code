/* $Id$ */

#include <iostream>
#include <string>
#include "home_theater_facade.h"
#include "amplifier.h"
#include "dvd_player.h"
#include "cd_player.h"
#include "projector.h"
#include "theater_lights.h"
#include "screen.h"
#include "popcorn_popper.h"
#include "tuner.h"

using std::cout;
using std::endl;
using std::string;

Home_Theater_Facade::Home_Theater_Facade(Amplifier *amp,
			Tuner *tuner,
			DVD_Player *dvd,
			CD_Player *cd,
			Projector *projector,
			Screen *screen,
			Theater_Lights *lights,
			Popcorn_Popper *popper) :
	amp_(amp), tuner_(tuner), dvd_(dvd), cd_(cd), 
	projector_(projector), screen_(screen), lights_(lights), popper_(popper)
{ }

Home_Theater_Facade::~Home_Theater_Facade()
{ }

void Home_Theater_Facade::watch_movie(string movie)
{
	cout << "Get ready to watch a movie..." << endl;
	popper_->on();
	popper_->pop();
	lights_->dim(10);
	screen_->down();
	projector_->on();
	projector_->wide_screen_mode();
	amp_->on();
	amp_->set_DVD(dvd_);
	amp_->set_surround_sound();
	amp_->set_volume(5);
	dvd_->on();
	dvd_->play(movie);
}

void Home_Theater_Facade::end_movie()
{
	cout << "Shutting movie theater down..." << endl;
	popper_->off();
	lights_->on();
	screen_->up();
	projector_->off();
	amp_->off();
	dvd_->stop();
	dvd_->eject();
	dvd_->off();
}

void Home_Theater_Facade::listen_to_CD(string cd_title)
{
	cout << "Get ready for an audiopile expreence..." << endl;
	lights_->on();
	amp_->on();
	amp_->set_volume(5);
	amp_->set_CD(cd_);
	amp_->set_stereo_sound();
	cd_->on();
	cd_->play(cd_title);
}

void Home_Theater_Facade::end_CD()
{
	cout << "Shutting down CD..." << endl;
	amp_->off();
	cd_->eject();
	cd_->off();
}

void Home_Theater_Facade::listen_to_radio(double frequency)
{
	cout << "Tuning in the airwaves..." << endl;
	tuner_->on();
	tuner_->set_frequency(frequency);
	amp_->on();
	amp_->set_volume(5);
	amp_->set_tuner(tuner_);
}

void Home_Theater_Facade::end_radio()
{
	cout << "Shutting down the tuner..." << endl;
	tuner_->off();
	amp_->off();
}
	
