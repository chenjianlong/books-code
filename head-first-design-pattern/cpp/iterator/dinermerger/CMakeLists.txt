PROJECT (diner_merger)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

ADD_DEFINITIONS (
	-D_CRT_SECURE_NO_WARNINGS
	)

SET (diner_merger_SOURCE_FILES
	alternating_diner_menu_iterator.cpp
	diner_menu.cpp
	diner_menu_iterator.cpp
	main.cpp
	menu_item.cpp
	menu_test_drive.cpp
	pancake_house_menu.cpp
	pancake_house_menu_iterator.cpp
	waitress.cpp
	)

ADD_EXECUTABLE (diner_merger ${diner_merger_SOURCE_FILES})
INSTALL (TARGETS diner_merger DESTINATION bin)

