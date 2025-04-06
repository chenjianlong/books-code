cmake_minimum_required(VERSION 3.15)
project(helloworld)

include_directories(
	${CMAKE_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${GTK3_INCLUDE_DIRS}
)

link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${GTK3_LIBRARY_DIRS}
)

add_definitions(
	-g
	${GTK3_CFLAGS}
)

set(SOURCE_FILES helloworld.c)

set (LIBS ${GTK3_LIBRARIES})

add_executable(helloworld ${SOURCE_FILES})
target_link_libraries(helloworld PRIVATE ${LIBS})
install(TARGETS helloworld
	BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
