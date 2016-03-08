PROJECT (cppnpv2_ch04)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

INCLUDE_DIRECTORIES(
	${ACE_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}
)

LINK_DIRECTORIES(
	${ACE_LIBRARY_DIRS}
)

ADD_DEFINITIONS (${ACE_DEFINITIONS})
SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ACE_C_FLAGS}")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ACE_CXX_FLAGS}")
SET (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${ACE_LINK_FLAGS}")

SET (rls_SOURCE_FILES
    select_reactor_ls_main.cpp
	logging_handler.cpp
	logging_event_handler.cpp
	logging_event_handler_ex.cpp
	logging_acceptor.cpp
	logging_acceptor_ex.cpp)

ADD_EXECUTABLE (select_reactor_logging_server ${rls_SOURCE_FILES})
TARGET_LINK_LIBRARIES (select_reactor_logging_server ${ACE_LIBRARIES})

SET (tp_rls_SOURCE_FILES
    tp_reactor_ls_main.cpp
	logging_handler.cpp
	logging_event_handler.cpp
	logging_event_handler_ex.cpp
	logging_acceptor.cpp
	logging_acceptor_ex.cpp)

ADD_EXECUTABLE (tp_reactor_logging_server ${tp_rls_SOURCE_FILES})
TARGET_LINK_LIBRARIES (tp_reactor_logging_server ${ACE_LIBRARIES})

IF (WIN32)

SET (wfmo_rls_SOURCE_FILES
    wfmo_reactor_ls_main.cpp
	logging_handler.cpp
	logging_event_handler.cpp
	logging_event_handler_ex.cpp
	logging_acceptor.cpp
	logging_acceptor_ex.cpp)

ADD_EXECUTABLE (wfmo_reactor_logging_server ${wfmo_rls_SOURCE_FILES})
TARGET_LINK_LIBRARIES (wfmo_reactor_logging_server ${ACE_LIBRARIES})

ENDIF (WIN32)
