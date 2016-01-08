PROJECT (cppnpv1_ch04)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

INCLUDE_DIRECTORIES (
	${ACE_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}
)

LINK_DIRECTORIES (
	${ACE_LIBRARY_DIRS}
)

ADD_DEFINITIONS (${ACE_DEFINITIONS} -g)

SET (mb_SOURCE_FILES message_block_demo.cpp)
ADD_EXECUTABLE (message_block_demo ${mb_SOURCE_FILES})
TARGET_LINK_LIBRARIES (message_block_demo ${ACE_LIBRARIES})

SET (ils_SOURCE_FILES
	logging_server.cpp
	logging_handler.cpp
	iterative_logging_server.cpp)

ADD_EXECUTABLE (iterative_logging_server ${ils_SOURCE_FILES})
TARGET_LINK_LIBRARIES (iterative_logging_server ${ACE_LIBRARIES})

SET (lc_SOURCE_FILES logging_client.cpp)
ADD_EXECUTABLE (logging_client ${lc_SOURCE_FILES})
TARGET_LINK_LIBRARIES (logging_client ${ACE_LIBRARIES})
