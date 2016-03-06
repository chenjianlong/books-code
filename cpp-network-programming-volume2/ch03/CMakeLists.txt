PROJECT (cppnpv2_ch03)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

INCLUDE_DIRECTORIES(
	${ACE_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}
)

LINK_DIRECTORIES(
	${ACE_LIBRARY_DIRS}
)

ADD_DEFINITIONS (${ACE_DEFINITIONS} -g)
SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ACE_C_FLAGS}")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ACE_CXX_FLAGS}")
SET (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${ACE_LINK_FLAGS}")

SET (la_SOURCE_FILES
	la_main.cpp
	logging_handler.cpp
	logging_event_handler.cpp
	logging_acceptor.cpp)

ADD_EXECUTABLE (logging_acceptor ${la_SOURCE_FILES})
TARGET_LINK_LIBRARIES (logging_acceptor ${ACE_LIBRARIES})

SET (la_ex_SOURCE_FILES
	la_ex_main.cpp
	logging_handler.cpp
	logging_event_handler.cpp
	logging_event_handler_ex.cpp
	logging_acceptor.cpp
	logging_acceptor_ex.cpp)

ADD_EXECUTABLE (logging_acceptor_ex ${la_ex_SOURCE_FILES})
TARGET_LINK_LIBRARIES (logging_acceptor_ex ${ACE_LIBRARIES})
