PROJECT (weather_station)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (weather_station_SOURCE_FILES
	current_conditions_display.cpp
	forecase_display.cpp
	heat_index_display.cpp
	main.cpp
	statistics_display.cpp
	weather_data.cpp
	weather_station.cpp
	)

ADD_EXECUTABLE (weather_station ${weather_station_SOURCE_FILES})
INSTALL (TARGETS weather_station DESTINATION bin)

