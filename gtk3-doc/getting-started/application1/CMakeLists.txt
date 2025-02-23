cmake_minimum_required(VERSION 3.15)
project(application1)

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

set(SOURCE_FILES
    exampleapp.h
    exampleapp.c
    exampleappwin.h
    exampleappwin.c
    main.c
)

set (LIBS ${GTK3_LIBRARIES})

add_executable(application1 ${SOURCE_FILES})
target_link_libraries(application1 PRIVATE ${LIBS})
install(TARGETS application1
	BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
