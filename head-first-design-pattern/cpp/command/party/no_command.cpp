/* $Id$ */

#include "no_command.h"

No_Command::No_Command()
{ }

No_Command::~No_Command()
{ }

void No_Command::execute()
{ }

void No_Command::undo()
{ }

std::string No_Command::to_string()
{
	return "No_Command";
}

