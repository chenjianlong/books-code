PROJECT (gumball)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (gumball_SOURCE_FILES
	gumball_machine.cpp
	gumball_machine_test_drive.cpp
	main.cpp
	)

ADD_EXECUTABLE (gumball ${gumball_SOURCE_FILES})
INSTALL (TARGETS gumball DESTINATION bin)

