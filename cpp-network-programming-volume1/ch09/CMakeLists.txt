PROJECT (cppnpv1_ch09)
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

SET (tpcs_SOURCE_FILES
	tpcls_main.cpp
	thread_per_connection_logging_server.cpp
	logging_server.cpp
	logging_handler.cpp)

ADD_EXECUTABLE (thread_per_connection_server ${tpcs_SOURCE_FILES})
TARGET_LINK_LIBRARIES (thread_per_connection_server ${ACE_LIBRARIES})

SET (rt_tpcs_SOURCE_FILES
	rt_tpcls_main.cpp
	rt_thread_per_connection_logging_server.cpp
	thread_per_connection_logging_server.cpp
	logging_server.cpp
	logging_handler.cpp)

ADD_EXECUTABLE (rt_thread_per_connection_server ${rt_tpcs_SOURCE_FILES})
TARGET_LINK_LIBRARIES (rt_thread_per_connection_server ${ACE_LIBRARIES})

SET (tss_tpcs_SOURCE_FILES
	tss_tpcls_main.cpp
	tss_thread_per_connection_logging_server.cpp
	thread_per_connection_logging_server.cpp
	logging_server.cpp
	logging_handler.cpp)

ADD_EXECUTABLE (tss_thread_per_connection_server ${tss_tpcs_SOURCE_FILES})
TARGET_LINK_LIBRARIES (tss_thread_per_connection_server ${ACE_LIBRARIES})
