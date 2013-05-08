/* $Id$ */

#include "ceiling_fan_off_command.h"

Ceiling_Fan_Off_Command::Ceiling_Fan_Off_Command(Ceiling_Fan &ceiling_fan) : ceiling_fan_(ceiling_fan), prev_speed_(0)
{ }

Ceiling_Fan_Off_Command::~Ceiling_Fan_Off_Command()
{ }

void Ceiling_Fan_Off_Command::execute()
{
	prev_speed_ = ceiling_fan_.get_speed();
	ceiling_fan_.off();
}

void Ceiling_Fan_Off_Command::undo()
{
	switch (prev_speed_) {
	case Ceiling_Fan::HIGH:
		ceiling_fan_.high();
		break;
	case Ceiling_Fan::MEDIUM:
		ceiling_fan_.medium();
		break;
	case Ceiling_Fan::LOW:
		ceiling_fan_.low();
		break;
	default:
		ceiling_fan_.off();
		break;
	}
}

std::string Ceiling_Fan_Off_Command::to_string()
{
	return "Ceiling_Fan_Off_Command";
}

