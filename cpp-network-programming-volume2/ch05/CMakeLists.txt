PROJECT (cppnpv2_ch05)
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

SET (starter_SOURCE_FILES
	service_reporter.cpp
	service_config_main.cpp)

ADD_EXECUTABLE (starter ${starter_SOURCE_FILES})
TARGET_LINK_LIBRARIES (starter ${ACE_LIBRARIES})

ADD_DEFINITIONS (-DBUILD_SLD_DLL)
SET (sld_SOURCE_FILES
	logging_event_handler.cpp
	logging_handler.cpp
	logging_acceptor.cpp
    SLD.cpp)

ADD_LIBRARY (SLD SHARED ${sld_SOURCE_FILES})
TARGET_LINK_LIBRARIES (SLD ${ACE_LIBRARIES})

ADD_DEFINITIONS (-DBUILD_SLDEX_DLL)
SET (sldex_SOURCE_FILES
	server_shutdown.cpp
	logging_event_handler_ex.cpp
	logging_event_handler.cpp
	logging_handler.cpp
	logging_acceptor.cpp
	logging_acceptor_ex.cpp
    SLD_ex.cpp)

ADD_LIBRARY (SLDex SHARED ${sldex_SOURCE_FILES})
TARGET_LINK_LIBRARIES (SLDex ${ACE_LIBRARIES})
