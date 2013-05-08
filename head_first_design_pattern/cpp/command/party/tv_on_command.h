/*!
 * \file tv_on_command.h
 * \brief The TV_On_Command class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-08
 */
/* $Id$ */

#ifndef TV_ON_COMMAND_H
#define TV_ON_COMMAND_H

#include <string>
#include "command.h"
#include "tv.h"

class TV_On_Command : public Command
{
public:
    TV_On_Command(TV &tv);
    virtual ~TV_On_Command();

	virtual void execute();
	virtual void undo();
	virtual std::string to_string();

protected:
	TV &tv_;
};

#endif /* TV_ON_COMMAND_H */

