PROJECT (dcl)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

INCLUDE_DIRECTORIES (
    ${BOOST_INCLUDE_DIRS}
)

LINK_DIRECTORIES (
    ${BOOST_LIBRARY_DIRS}
)

SET (dcl_SOURCE_FILES
    main.cpp
    singleton.cpp
    singleton_client.cpp
    )

ADD_EXECUTABLE (dcl ${dcl_SOURCE_FILES})
IF (APPLE)
	TARGET_LINK_LIBRARIES (dcl boost_system)
ENDIF (APPLE)
INSTALL (TARGETS dcl DESTINATION bin)

