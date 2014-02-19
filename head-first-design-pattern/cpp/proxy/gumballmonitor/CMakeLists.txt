PROJECT (gumball_monitor)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (gumball_monitor_SOURCE_FILES
	gumball_machine.cpp
	gumball_monitor.cpp
	gumball_machine_test_drive.cpp
	has_quarter_state.cpp
	main.cpp
	no_quarter_state.cpp
	sold_out_state.cpp
	sold_state.cpp
	winner_state.cpp
	)

ADD_EXECUTABLE (gumball_monitor ${gumball_monitor_SOURCE_FILES})
INSTALL (TARGETS gumball_monitor DESTINATION bin)

