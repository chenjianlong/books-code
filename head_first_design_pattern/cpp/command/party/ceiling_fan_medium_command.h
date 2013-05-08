/*!
 * \file ceiling_fan_medium_command.h
 * \brief The Ceiling_Fan_Medium_Command class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-08
 */
/* $Id$ */

#ifndef CEILING_FAN_MEDIUM_COMMAND_H
#define CEILING_FAN_MEDIUM_COMMAND_H

#include <string>
#include "command.h"
#include "ceiling_fan.h"

class Ceiling_Fan_Medium_Command : public Command
{
public:
    Ceiling_Fan_Medium_Command(Ceiling_Fan &ceiling_fan);
    virtual ~Ceiling_Fan_Medium_Command();

	virtual void execute();
	virtual void undo();
	virtual std::string to_string();

protected:
	Ceiling_Fan &ceiling_fan_;
	int prev_speed_;
};

#endif /* CEILING_FAN_MEDIUM_COMMAND_H */

