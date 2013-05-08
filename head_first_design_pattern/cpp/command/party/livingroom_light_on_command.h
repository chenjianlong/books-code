/*!
 * \file livingroom_light_on_command.h
 * \brief The Livingroom_Light_On_Command class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-08
 */
/* $Id$ */

#ifndef LIVINGROOM_LIGHT_ON_COMMAND_H
#define LIVINGROOM_LIGHT_ON_COMMAND_H

#include <string>
#include "command.h"
#include "light.h"

class Livingroom_Light_On_Command : public Command
{
public:
    Livingroom_Light_On_Command(Light &light);
    virtual ~Livingroom_Light_On_Command();

	virtual void execute();
	virtual void undo();
	virtual std::string to_string();

protected:
	Light &light_;
};

#endif /* LIVINGROOM_LIGHT_ON_COMMAND_H */

