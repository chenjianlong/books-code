/*!
 * \file livingroom_light_off_command.h
 * \brief The Livingroom_Light_Off_Command class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-08
 */
/* $Id$ */

#ifndef LIVINGROOM_LIGHT_OFF_COMMAND_H
#define LIVINGROOM_LIGHT_OFF_COMMAND_H

#include <string>
#include "command.h"
#include "light.h"

class Livingroom_Light_Off_Command : public Command
{
public:
    Livingroom_Light_Off_Command(Light &light);
    virtual ~Livingroom_Light_Off_Command();

	virtual void execute();
	virtual void undo();
	virtual std::string to_string();

protected:
	Light &light_;
};

#endif /* LIVINGROOM_LIGHT_OFF_COMMAND_H */

