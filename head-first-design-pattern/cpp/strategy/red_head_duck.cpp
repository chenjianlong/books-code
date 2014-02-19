/* $Id$ */

#include <iostream>
#include "red_head_duck.h"
#include "fly_with_wings.h"
#include "quack.h"

Red_Head_Duck::Red_Head_Duck()
{
    set_fly_behavior(new Fly_With_Wings());
    set_quack_behavior(new Quack());
}

Red_Head_Duck::~Red_Head_Duck()
{ }

void Red_Head_Duck::display()
{
    std::cout << "I'm a real Red Headed duck" << std::endl;
}
