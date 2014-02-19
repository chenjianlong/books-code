/*!
 * \file light_on_command.h
 * \brief The Light_On_Command class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-08
 */
/* $Id$ */

#ifndef LIGHT_ON_COMMAND_H
#define LIGHT_ON_COMMAND_H

#include <string>
#include "command.h"
#include "light.h"

class Light_On_Command : public Command
{
public:
    Light_On_Command(Light &light);
    virtual ~Light_On_Command();

	virtual void execute();
	virtual void undo();
	virtual std::string to_string();

protected:
	Light &light_;
};

#endif /* LIGHT_ON_COMMAND_H */

