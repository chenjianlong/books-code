PROJECT (pizza_factory_method)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (pizza_factory_method_SOURCE_FILES
	chicago_pizza_store.cpp
	chicago_style_cheese_pizza.cpp
	chicago_style_clam_pizza.cpp
	chicago_style_pepperoni_pizza.cpp
	chicago_style_veggie_pizza.cpp
	main.cpp
	ny_pizza_store.cpp
	ny_style_cheese_pizza.cpp
	ny_style_clam_pizza.cpp
	ny_style_pepperoni_pizza.cpp
	ny_style_veggie_pizza.cpp
	pizza.cpp
	pizza_store.cpp
	pizza_test_drive.cpp
	)

ADD_EXECUTABLE (pizza_factory_method ${pizza_factory_method_SOURCE_FILES})
INSTALL (TARGETS pizza_factory_method DESTINATION bin)

