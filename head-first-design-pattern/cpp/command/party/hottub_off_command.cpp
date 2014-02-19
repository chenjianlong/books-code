/* $Id$ */

#include "hottub_off_command.h"

Hottub_Off_Command::Hottub_Off_Command(Hottub &hottub) : hottub_(hottub)
{ }

Hottub_Off_Command::~Hottub_Off_Command()
{ }

void Hottub_Off_Command::execute()
{
	hottub_.set_temperature(98);
	hottub_.off();
}

void Hottub_Off_Command::undo()
{
	hottub_.on();
}

std::string Hottub_Off_Command::to_string()
{
	return "Hottub_Off_Command";
}

