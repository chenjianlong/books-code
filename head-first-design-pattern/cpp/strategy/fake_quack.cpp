/* $Id$ */

#include <iostream>
#include "fake_quack.h"

Fake_Quack::Fake_Quack()
{ }

Fake_Quack::~Fake_Quack()
{ }

void Fake_Quack::quack()
{
    std::cout << "Qwak" << std::endl;
}
