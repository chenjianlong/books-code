PROJECT (pizza_abstract_factory)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

INCLUDE_DIRECTORIES (
    $ENV{BOOST_ROOT}
)

SET (pizza_abstract_factory_SOURCE_FILES
    black_olives.cpp
    cheese_pizza.cpp
    chicago_pizza_ingredient_factory.cpp
    chicago_pizza_store.cpp
    clam_pizza.cpp
    eggplant.cpp
    fresh_clams.cpp
    frozen_clams.cpp
    garlic.cpp
    main.cpp
    marinara_sauce.cpp
    mozzarella_cheese.cpp
    mushroom.cpp
    ny_pizza_ingredient_factory.cpp
    ny_pizza_store.cpp
    onion.cpp
    parmesam_cheese.cpp
    pepperoni_pizza.cpp
    pizza.cpp
    pizza_store.cpp
    pizza_test_drive.cpp
    plum_tomato_sauce.cpp
    red_pepper.cpp
    reggiano_cheese.cpp
    sliced_pepperoni.cpp
    spinach.cpp
    thick_crust_dough.cpp
    thin_crust_dough.cpp
    veggie_pizza.cpp
    )

ADD_EXECUTABLE (pizza_abstract_factory ${pizza_abstract_factory_SOURCE_FILES})
INSTALL (TARGETS pizza_abstract_factory DESTINATION bin)

