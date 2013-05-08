/*!
 * \file no_command.h
 * \brief The No_Command class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-07
 */
/* $Id$ */

#ifndef NO_COMMAND_H
#define NO_COMMAND_H

#include <string>
#include "command.h"

class No_Command : public Command
{
public:
    No_Command();
    virtual ~No_Command();

	virtual void execute();
	virtual void undo();
	virtual std::string to_string();
};

#endif /* NO_COMMAND_H */

