PROJECT (barista)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (barista_SOURCE_FILES
	beverage_test_drive.cpp
	caffeine_beverage.cpp
	caffeiner_beverage_with_hook.cpp
	coffee.cpp
	coffee_with_hook.cpp
	main.cpp
	tea.cpp
	tea_with_hook.cpp
	)

ADD_EXECUTABLE (barista ${barista_SOURCE_FILES})
INSTALL (TARGETS barista DESTINATION bin)

