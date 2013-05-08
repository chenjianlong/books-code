/* $Id$ */

#include "stereo_on_command.h"

Stereo_On_Command::Stereo_On_Command(Stereo &stereo) : stereo_(stereo)
{ }

Stereo_On_Command::~Stereo_On_Command()
{ }

void Stereo_On_Command::execute()
{
	stereo_.on();
}

void Stereo_On_Command::undo()
{
	stereo_.off();
}

std::string Stereo_On_Command::to_string()
{
	return "Stereo_On_Command";
}

