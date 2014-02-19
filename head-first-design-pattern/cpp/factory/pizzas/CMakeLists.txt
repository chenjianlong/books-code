PROJECT (simple_pizza_factory)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (simple_pizza_factory_SOURCE_FILES
	cheese_pizza.cpp
	clam_pizza.cpp
	main.cpp
	pepperon_pizza.cpp
	pizza.cpp
	pizza_store.cpp
	pizza_test_drive.cpp
	simple_pizza_factory.cpp
	veggie_pizza.cpp
	)

ADD_EXECUTABLE (simple_pizza_factory ${simple_pizza_factory_SOURCE_FILES})
INSTALL (TARGETS simple_pizza_factory DESTINATION bin)
