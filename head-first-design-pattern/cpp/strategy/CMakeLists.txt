PROJECT (mini_duck_simulator)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (mini_duck_simulator_SOURCE_FILES
    decoy_duck.cpp
    duck.cpp
    fake_quack.cpp
    fly_no_way.cpp
    fly_rocket_powered.cpp
    fly_with_wings.cpp
    main.cpp
    mallard_duck.cpp
    mini_duck_simulator.cpp
    model_duck.cpp
    mute_quack.cpp
    quack.cpp
    red_head_duck.cpp
    rubber_duck.cpp
    squeak.cpp
    )

ADD_EXECUTABLE (mini_duck_simulator ${mini_duck_simulator_SOURCE_FILES})
INSTALL (TARGETS mini_duck_simulator DESTINATION bin)

