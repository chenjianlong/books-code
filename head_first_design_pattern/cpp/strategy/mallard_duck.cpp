/* $Id$ */

#include <iostream>
#include "mallard_duck.h"
#include "quack.h"
#include "fly_with_wings.h"

Mallard_Duck::Mallard_Duck()
{ 
    set_quack_behavior(new Quack());
    set_fly_behavior(new Fly_With_Wings());
}

Mallard_Duck::~Mallard_Duck()
{ }

void Mallard_Duck::display()
{
    std::cout << "I'm a real Mallard duck" << std::endl;
}
