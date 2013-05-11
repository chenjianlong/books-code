PROJECT (ducks_adapter)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (ducks_adapter_SOURCE_FILES
	duck_adapter.cpp
	duck_test_drive.cpp
	main.cpp
	mallard_duck.cpp
	turkey_adapter.cpp
	turkey_test_drive.cpp
	wild_turkey.cpp
	)

ADD_EXECUTABLE (ducks_adapter ${ducks_adapter_SOURCE_FILES})
INSTALL (TARGETS ducks_adapter DESTINATION bin)

