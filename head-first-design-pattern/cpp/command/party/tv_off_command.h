/*!
 * \file tv_off_command.h
 * \brief The TV_Off_Command class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-08
 */
/* $Id$ */

#ifndef TV_OFF_COMMAND_H
#define TV_OFF_COMMAND_H

#include <string>
#include "command.h"
#include "tv.h"

class TV_Off_Command : public Command
{
public:
    TV_Off_Command(TV &tv);
    virtual ~TV_Off_Command();

	virtual void execute();
	virtual void undo();
	virtual std::string to_string();

protected:
	TV &tv_;
};

#endif /* TV_OFF_COMMAND_H */

