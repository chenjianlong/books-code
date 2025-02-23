cmake_minimum_required(VERSION 3.15)
project(application8)

set(resources_output ${CMAKE_CURRENT_BINARY_DIR}/resources.c)

add_custom_command(
	OUTPUT ${resources_output}
	COMMAND glib-compile-resources exampleapp.gresource.xml --target=${resources_output} --generate-source
	DEPENDS exampleapp.gresource.xml window.ui app-menu.ui prefs.ui
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
    exampleappprefs.h
    exampleappprefs.c
    exampleappwin.h
    exampleappwin.c
    main.c
)

set (LIBS ${GTK3_LIBRARIES})

add_schema(${CMAKE_CURRENT_SOURCE_DIR}/org.gtk.exampleapp.gschema.xml SCHEMA_OUTPUT)

add_executable(application8 ${SOURCE_FILES})
target_link_libraries(application8 PRIVATE ${LIBS})
install(TARGETS application8
	BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
