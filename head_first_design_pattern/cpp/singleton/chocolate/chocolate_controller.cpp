/* $Id$ */

#include "chocolate_controller.h"
#include "chocolate_boiler.h"

Chocolate_Controller::Chocolate_Controller()
{ }

Chocolate_Controller::~Chocolate_Controller()
{ }

int Chocolate_Controller::main(int argc, char *argv[])
{
	Chocolate_Boiler *boiler = Chocolate_Boiler::get_instance();
	boiler->fill();
	boiler->boil();
	boiler->drain();

	Chocolate_Boiler *boiler2 = Chocolate_Boiler::get_instance();

	Chocolate_Boiler::close();
	Chocolate_Boiler::get_instance();

	return 0;
}

