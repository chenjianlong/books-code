/* $Id$ */

#include "stereo_off_command.h"

Stereo_Off_Command::Stereo_Off_Command(Stereo &stereo) : stereo_(stereo)
{ }

Stereo_Off_Command::~Stereo_Off_Command()
{ }

void Stereo_Off_Command::execute()
{
	stereo_.off();
}

void Stereo_Off_Command::undo()
{
	stereo_.on();
}

std::string Stereo_Off_Command::to_string()
{
	return "Stereo_Off_Command";
}

