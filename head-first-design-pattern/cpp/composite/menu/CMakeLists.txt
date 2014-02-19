PROJECT (menu)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

INCLUDE_DIRECTORIES (
	${BOOST_INCLUDE_DIRS}
)

SET (menu_SOURCE_FILES
	main.cpp
	menu.cpp
	menu_component.cpp
	menu_item.cpp
	menu_test_drive.cpp
	waitress.cpp
	)

ADD_EXECUTABLE (menu ${menu_SOURCE_FILES})
INSTALL (TARGETS menu DESTINATION bin)

