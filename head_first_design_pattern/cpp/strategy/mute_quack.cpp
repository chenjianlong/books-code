/* $Id$ */

#include <iostream>
#include "mute_quack.h"

Mute_Quack::Mute_Quack()
{ }

Mute_Quack::~Mute_Quack()
{ }

void Mute_Quack::quack()
{
    std::cout << "<< Silence >>" << std::endl;
}
