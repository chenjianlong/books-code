/*!
 * \file light_off_command.h
 * \brief The Light_Off_Command class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-08
 */
/* $Id$ */

#ifndef LIGHT_OFF_COMMAND_H
#define LIGHT_OFF_COMMAND_H

#include <string>
#include "command.h"
#include "light.h"

class Light_Off_Command : public Command
{
public:
    Light_Off_Command(Light &light);
    virtual ~Light_Off_Command();

	virtual void execute();
	virtual void undo();
	virtual std::string to_string();

protected:
	Light &light_;
};

#endif /* LIGHT_OFF_COMMAND_H */

