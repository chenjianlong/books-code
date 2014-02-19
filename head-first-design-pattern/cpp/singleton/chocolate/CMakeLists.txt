PROJECT (chocolate_boiler)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (chocolate_boiler_SOURCE_FILES
	chocolate_boiler.cpp
	chocolate_controller.cpp
	main.cpp
	)

ADD_EXECUTABLE (chocolate_boiler ${chocolate_boiler_SOURCE_FILES})
INSTALL (TARGETS chocolate_boiler DESTINATION bin)
