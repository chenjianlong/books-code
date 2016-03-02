PROJECT (cppnpv1_ch08)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

INCLUDE_DIRECTORIES(
	${ACE_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}
)

LINK_DIRECTORIES(
	${ACE_LIBRARY_DIRS}
)

ADD_DEFINITIONS (${ACE_DEFINITIONS} -g)

SET (factorial_SOURCE_FILES
	process_factorial.cpp)

ADD_EXECUTABLE (process_factorial ${factorial_SOURCE_FILES})
TARGET_LINK_LIBRARIES (process_factorial ${ACE_LIBRARIES})

SET (factorial2_SOURCE_FILES
	process_factorial2.cpp)

ADD_EXECUTABLE (process_factorial2 ${factorial2_SOURCE_FILES})
TARGET_LINK_LIBRARIES (process_factorial2 ${ACE_LIBRARIES})

SET (ppcs_SOURCE_FILES
	process_per_connection_logging_server.cpp
	logging_server.cpp
	logging_handler.cpp
	logging_process.cpp)

ADD_EXECUTABLE (process_per_connection_server ${ppcs_SOURCE_FILES})
TARGET_LINK_LIBRARIES (process_per_connection_server ${ACE_LIBRARIES})
