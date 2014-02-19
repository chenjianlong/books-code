PROJECT (starbuzz_coffee)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (starbuzz_coffee_SOURCE_FILES
	dark_roast.cpp
	decaf.cpp
	espresso.cpp
	house_blend.cpp
	main.cpp
	milk.cpp
	mocha.cpp
	soy.cpp
	starbuzz_coffee.cpp
	whip.cpp
	)

ADD_EXECUTABLE (starbuzz_coffee ${starbuzz_coffee_SOURCE_FILES})
INSTALL (TARGETS starbuzz_coffee DESTINATION bin)

