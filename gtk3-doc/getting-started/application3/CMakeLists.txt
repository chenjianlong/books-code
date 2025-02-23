cmake_minimum_required(VERSION 3.15)
project(application3)

set(resources_output ${CMAKE_CURRENT_BINARY_DIR}/resources.c)

add_custom_command(
	OUTPUT ${resources_output}
	COMMAND glib-compile-resources exampleapp.gresource.xml --target=${resources_output} --generate-source
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/exampleapp.gresource.xml ${CMAKE_CURRENT_SOURCE_DIR}/window.ui
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMENT "Generate resources.c"
)

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
    ${resources_output}
    exampleapp.h
    exampleapp.c
    exampleappwin.h
    exampleappwin.c
    main.c
)

set (LIBS ${GTK3_LIBRARIES})

add_executable(application3 ${SOURCE_FILES})
target_link_libraries(application3 PRIVATE ${LIBS})
install(TARGETS application3
	BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
