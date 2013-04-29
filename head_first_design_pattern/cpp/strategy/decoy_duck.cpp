/* $Id$ */

#include <iostream>
#include "decoy_duck.h"
#include "fly_no_way.h"
#include "mute_quack.h"

Decoy_Duck::Decoy_Duck()
{ 
    set_fly_behavior(new Fly_No_Way());
    set_quack_behavior(new Mute_Quack());
}

Decoy_Duck::~Decoy_Duck()
{ }

void Decoy_Duck::display()
{
    std::cout << "I'm a duck Decoy" << std::endl;
}
