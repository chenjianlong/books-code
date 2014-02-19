/* $Id$ */

#include "light_off_command.h"

Light_Off_Command::Light_Off_Command(Light &light) : light_(light)
{ }

Light_Off_Command::~Light_Off_Command()
{ }

void Light_Off_Command::execute()
{
	light_.off();
}

void Light_Off_Command::undo()
{
	light_.on();
}

std::string Light_Off_Command::to_string()
{
	return "Light_Off_Command";
}

