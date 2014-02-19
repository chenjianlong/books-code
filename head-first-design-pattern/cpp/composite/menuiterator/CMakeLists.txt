PROJECT (menu_iterator)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

INCLUDE_DIRECTORIES (
	${BOOST_INCLUDE_DIRS}
)

SET (menu_iterator_SOURCE_FILES
	composite_iterator.cpp
	main.cpp
	menu.cpp
	menu_component.cpp
	menu_item.cpp
	menu_test_drive.cpp
	null_iterator.cpp
	waitress.cpp
	)

ADD_EXECUTABLE (menu_iterator ${menu_iterator_SOURCE_FILES})
INSTALL (TARGETS menu_iterator DESTINATION bin)

