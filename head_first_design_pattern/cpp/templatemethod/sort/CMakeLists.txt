PROJECT (sort)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (sort_SOURCE_FILES
	duck.cpp
	duck_sort_test_drive.cpp
	main.cpp
	)

ADD_EXECUTABLE (sort ${sort_SOURCE_FILES})
INSTALL (TARGETS sort DESTINATION bin)

