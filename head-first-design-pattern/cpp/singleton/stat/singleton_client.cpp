/* $Id$ */

#include "singleton_client.h"
#include "singleton.h"

Singleton_Client::Singleton_Client()
{ }

Singleton_Client::~Singleton_Client()
{ }

int Singleton_Client::main(int argc, char *argv[])
{
    volatile Singleton *singleton = Singleton::get_instance();

    return 0;
}

