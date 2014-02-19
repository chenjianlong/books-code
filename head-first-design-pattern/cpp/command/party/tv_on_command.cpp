/* $Id$ */

#include "tv_on_command.h"

TV_On_Command::TV_On_Command(TV &tv) : tv_(tv)
{ }

TV_On_Command::~TV_On_Command()
{ }

void TV_On_Command::execute()
{
	tv_.on();
	tv_.set_input_channel();
}

void TV_On_Command::undo()
{
	tv_.off();
}

std::string TV_On_Command::to_string()
{
	return "TV_On_Command";
}

