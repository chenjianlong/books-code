/*!
 * \file ceiling_fan_high_command.h
 * \brief The Ceiling_Fan_High_Command class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-07
 */
/* $Id$ */

#ifndef CEILING_FAN_HIGH_COMMAND_H
#define CEILING_FAN_HIGH_COMMAND_H

#include "command.h"
#include "ceiling_fan.h"

class Ceiling_Fan_High_Command : public Command
{
public:
    Ceiling_Fan_High_Command(Ceiling_Fan &ceiling_fan);
    virtual ~Ceiling_Fan_High_Command();

	virtual void execute();
	virtual void undo();
	virtual std::string to_string();

protected:
	Ceiling_Fan &ceiling_fan_;
	int prev_speed_;
};

#endif /* CEILING_FAN_HIGH_COMMAND_H */

