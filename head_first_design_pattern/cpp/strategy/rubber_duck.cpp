/* $Id$ */

#include <iostream>
#include "rubber_duck.h"
#include "fly_no_way.h"
#include "squeak.h"

Rubber_Duck::Rubber_Duck()
{ 
    set_fly_behavior(new Fly_No_Way());
    set_quack_behavior(new Squeak());
}

Rubber_Duck::~Rubber_Duck()
{ }

void Rubber_Duck::display()
{
    std::cout << "I'm a rubber duckie" << std::endl;
}
