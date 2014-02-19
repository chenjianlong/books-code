/*!
 * \file macro_command.h
 * \brief The Macro_Command class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-08
 */
/* $Id$ */

#ifndef MACRO_COMMAND_H
#define MACRO_COMMAND_H

#include <vector>
#include "command.h"


class Macro_Command : public Command
{
public:
    Macro_Command(COMMANDS &commands);
    virtual ~Macro_Command();

	virtual void execute();
	virtual void undo();
	virtual std::string to_string();

protected:
	COMMANDS &commands_;
};

#endif /* MACRO_COMMAND_H */

