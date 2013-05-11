/* $Id$ */

#include "home_theater_test_drive.h"
#include "home_theater_facade.h"
#include "amplifier.h"
#include "tuner.h"
#include "dvd_player.h"
#include "cd_player.h"
#include "projector.h"
#include "theater_lights.h"
#include "screen.h"
#include "popcorn_popper.h"


Home_Theater_Test_Drive::Home_Theater_Test_Drive()
{ }

Home_Theater_Test_Drive::~Home_Theater_Test_Drive()
{ }

int Home_Theater_Test_Drive::main(int argc, char *argv[])
{
	Amplifier amp("Top-O-Line Amplifier");
	Tuner tuner("Top-O-Line AM/FM Tuner", &amp);
	DVD_Player dvd("Top-O-Line DVD Player", &amp);
	CD_Player cd("Top-O-Line CD Player", &amp);
	Projector projector("Top-O-Line Projector", &dvd);
	Theater_Lights lights("Theater Ceiling Lights");
	Screen screen("Theater Screen");
	Popcorn_Popper popper("Popcorn Popper");

	Home_Theater_Facade home_theater(&amp, &tuner, &dvd, &cd, 
			&projector, &screen, &lights, &popper);

	home_theater.watch_movie("Raiders of the Lost Ark");
	home_theater.end_movie();

	return 0;
}

