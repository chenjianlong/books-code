PROJECT (ace_internal_ch04)
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

SET (task_SOURCE_FILES task.cpp)
ADD_EXECUTABLE (task ${task_SOURCE_FILES})
TARGET_LINK_LIBRARIES (task ${ACE_LIBRARIES})

SET (active_object_SOURCE_FILES active_object.cpp)
ADD_EXECUTABLE (active_object ${active_object_SOURCE_FILES})
TARGET_LINK_LIBRARIES (active_object ${ACE_LIBRARIES})
