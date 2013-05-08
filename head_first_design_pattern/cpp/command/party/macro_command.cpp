/* $Id$ */

#include "macro_command.h"

Macro_Command::Macro_Command(COMMANDS &commands) : commands_(commands)
{ }

Macro_Command::~Macro_Command()
{ }

void Macro_Command::execute()
{
	for (COMMANDS::iterator it = commands_.begin(); it != commands_.end(); it++) {
		(*it)->execute();
	}
}

void Macro_Command::undo()
{
	for (COMMANDS::iterator it = commands_.begin(); it != commands_.end(); it++) {
		(*it)->undo();
	}
}

std::string Macro_Command::to_string()
{
	return "Macro_Command";
}

