/* $Id$ */

#include "singleton.h"

volatile Singleton *Singleton::unique_(new Singleton());

Singleton::Singleton()
{ }

Singleton::~Singleton()
{ }

volatile Singleton *Singleton::get_instance()
{
    return unique_;
}

