PROJECT (simple_barista)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (simple_barista_SOURCE_FILES
	barista.cpp
	coffee.cpp
	main.cpp
	tea.cpp
	)

ADD_EXECUTABLE (simple_barista ${simple_barista_SOURCE_FILES})
INSTALL (TARGETS simple_barista DESTINATION bin)

