PROJECT (cppnpv1_ch07)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

INCLUDE_DIRECTORIES (
	${ACE_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}
)

LINK_DIRECTORIES (
	${ACE_LIBRARY_DIRS}
)

ADD_DEFINITIONS (${ACE_DEFINITIONS} -g)

SET (rls_SOURCE_FILES
	reactive_logging_server.cpp
	logging_server.cpp
	logging_handler.cpp
	iterative_logging_server.cpp)

ADD_EXECUTABLE (reactive_logging_server ${rls_SOURCE_FILES})
TARGET_LINK_LIBRARIES (reactive_logging_server ${ACE_LIBRARIES})

SET (rls2_SOURCE_FILES
	reactive_logging_server2.cpp
	logging_server.cpp
	logging_handler.cpp
	iterative_logging_server.cpp)

ADD_EXECUTABLE (reactive_logging_server2 ${rls2_SOURCE_FILES})
TARGET_LINK_LIBRARIES (reactive_logging_server2 ${ACE_LIBRARIES})

SET (rls3_SOURCE_FILES
	reactive_logging_server3.cpp
	logging_server.cpp
	logging_handler.cpp
	iterative_logging_server.cpp)

ADD_EXECUTABLE (reactive_logging_server3 ${rls3_SOURCE_FILES})
TARGET_LINK_LIBRARIES (reactive_logging_server3 ${ACE_LIBRARIES})

SET (rls4_SOURCE_FILES
	reactive_logging_server4.cpp
	logging_server.cpp
	logging_handler.cpp
	iterative_logging_server.cpp)

ADD_EXECUTABLE (reactive_logging_server_ex ${rls4_SOURCE_FILES})
TARGET_LINK_LIBRARIES (reactive_logging_server_ex ${ACE_LIBRARIES})
