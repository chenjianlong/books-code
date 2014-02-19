/* $Id$ */

#include "hottub_on_command.h"

Hottub_On_Command::Hottub_On_Command(Hottub &hottub) : hottub_(hottub)
{ }

Hottub_On_Command::~Hottub_On_Command()
{ }

void Hottub_On_Command::execute()
{
	hottub_.on();
	hottub_.set_temperature(104);
	hottub_.circulate();
}

void Hottub_On_Command::undo()
{
	hottub_.off();
}

std::string Hottub_On_Command::to_string()
{
	return "Hottub_On_Command";
}

