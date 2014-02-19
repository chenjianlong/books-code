/* $Id$ */

#include "tv_off_command.h"

TV_Off_Command::TV_Off_Command(TV &tv) : tv_(tv)
{ }

TV_Off_Command::~TV_Off_Command()
{ }

void TV_Off_Command::execute()
{
	tv_.off();
}

void TV_Off_Command::undo()
{
	tv_.on();
}

std::string TV_Off_Command::to_string()
{
	return "TV_Off_Command";
}

