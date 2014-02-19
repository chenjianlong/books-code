/* $Id$ */

#include "mini_duck_simulator.h"
#include "mallard_duck.h"
#include "rubber_duck.h"
#include "decoy_duck.h"
#include "model_duck.h"
#include "fly_rocket_powered.h"

Mini_Duck_Simulator::Mini_Duck_Simulator()
{ }

Mini_Duck_Simulator::~Mini_Duck_Simulator()
{ }

int Mini_Duck_Simulator::main(int argc, char *argv[])
{
    Mallard_Duck mallard;
    Rubber_Duck rubber;
    Decoy_Duck decoy;
    Model_Duck model;

    mallard.perform_quack();
    rubber.perform_quack();
    decoy.perform_quack();

    model.perform_fly();
    model.set_fly_behavior(new Fly_Rocket_Powered());
    model.perform_fly();

    return 0;
}
