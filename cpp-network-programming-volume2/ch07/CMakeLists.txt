PROJECT (cppnpv2_ch07)
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

ADD_DEFINITIONS (-DBUILD_TPCLS_DLL)
SET (tpcls_SOURCE_FILES
	logging_handler.cpp
	tpc_logging_handler.cpp
	tpc_logging_acceptor.cpp)

ADD_LIBRARY (TPCLS SHARED ${tpcls_SOURCE_FILES})
TARGET_LINK_LIBRARIES (TPCLS ${ACE_LIBRARIES})

ADD_DEFINITIONS (-DBUILD_AC_CLD_DLL)
SET (ac_cld_SOURCE_FILES
	ac_cld_acceptor.cpp
	ac_cld_connector.cpp
	ac_client_logging_daemon.cpp
	ac_input_handler.cpp
	ac_output_handler.cpp
	logging_handler.cpp)

ADD_LIBRARY (AC_CLD SHARED ${ac_cld_SOURCE_FILES})
TARGET_LINK_LIBRARIES (AC_CLD ${ACE_LIBRARIES})
