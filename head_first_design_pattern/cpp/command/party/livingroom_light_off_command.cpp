/* $Id$ */

#include "livingroom_light_off_command.h"

Livingroom_Light_Off_Command::Livingroom_Light_Off_Command(Light &light) : light_(light)
{ }

Livingroom_Light_Off_Command::~Livingroom_Light_Off_Command()
{ }

void Livingroom_Light_Off_Command::execute()
{
	light_.off();
}

void Livingroom_Light_Off_Command::undo()
{
	light_.on();
}

std::string Livingroom_Light_Off_Command::to_string()
{
	return "Livingroom_Light_Off_Command";
}

