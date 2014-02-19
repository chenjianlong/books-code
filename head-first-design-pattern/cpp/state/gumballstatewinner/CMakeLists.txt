PROJECT (gumball_state_winner)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (gumball_state_winner_SOURCE_FILES
	gumball_machine.cpp
	gumball_machine_test_drive.cpp
	has_quarter_state.cpp
	main.cpp
	no_quarter_state.cpp
	sold_out_state.cpp
	sold_state.cpp
	winner_state.cpp
	)

ADD_EXECUTABLE (gumball_state_winner ${gumball_state_winner_SOURCE_FILES})
INSTALL (TARGETS gumball_state_winner DESTINATION bin)

