/* $Id$ */

#include "stereo_on_with_cd_command.h"

Stereo_On_With_CD_Command::Stereo_On_With_CD_Command(Stereo &stereo) : stereo_(stereo)
{ }

Stereo_On_With_CD_Command::~Stereo_On_With_CD_Command()
{ }

void Stereo_On_With_CD_Command::execute()
{
	stereo_.on();
	stereo_.set_CD();
	stereo_.set_volume(11);
}

void Stereo_On_With_CD_Command::undo()
{
	stereo_.off();
}

std::string Stereo_On_With_CD_Command::to_string()
{
	return "Stereo_On_With_CD_Command";
}

