PROJECT (home_theater)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (home_theater_SOURCE_FILES
	amplifier.cpp
	cd_player.cpp
	dvd_player.cpp
	home_theater_facade.cpp
	home_theater_test_drive.cpp
	main.cpp
	popcorn_popper.cpp
	projector.cpp
	screen.cpp
	theater_lights.cpp
	tuner.cpp
	)

ADD_EXECUTABLE (home_theater ${home_theater_SOURCE_FILES})
INSTALL (TARGETS home_theater DESTINATION bin)

