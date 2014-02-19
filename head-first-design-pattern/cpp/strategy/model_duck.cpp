/* $Id$ */

#include <iostream>
#include "model_duck.h"
#include "fly_no_way.h"
#include "quack.h"

Model_Duck::Model_Duck()
{
    set_fly_behavior(new Fly_No_Way());
    set_quack_behavior(new Quack());
}

Model_Duck::~Model_Duck()
{ }

void Model_Duck::display()
{
    std::cout << "I'm a model duck" << std::endl;
}

