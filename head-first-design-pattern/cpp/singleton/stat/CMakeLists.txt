PROJECT (stat)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (stat_SOURCE_FILES
    main.cpp
    singleton.cpp
    singleton_client.cpp
    )

ADD_EXECUTABLE (stat ${stat_SOURCE_FILES})
INSTALL (TARGETS stat DESTINATION bin)

