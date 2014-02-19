/* $Id$ */

#include "livingroom_light_on_command.h"

Livingroom_Light_On_Command::Livingroom_Light_On_Command(Light &light) : light_(light)
{ }

Livingroom_Light_On_Command::~Livingroom_Light_On_Command()
{ }

void Livingroom_Light_On_Command::execute()
{
	light_.on();
}

void Livingroom_Light_On_Command::undo()
{
	light_.off();
}

std::string Livingroom_Light_On_Command::to_string()
{
	return "Livingroom_Light_On_Command";
}

