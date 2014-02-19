/* $Id$ */

#include "light_on_command.h"

Light_On_Command::Light_On_Command(Light &light) : light_(light)
{ }

Light_On_Command::~Light_On_Command()
{ }

void Light_On_Command::execute()
{
	light_.on();
}

void Light_On_Command::undo()
{
	light_.off();
}

std::string Light_On_Command::to_string()
{
	return "Light_On_Command";
}

