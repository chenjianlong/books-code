/*!
 * \file hottub_off_command.h
 * \brief The Hottub_Off_Command class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-08
 */
/* $Id$ */

#ifndef HOTTUB_OFF_COMMAND_H
#define HOTTUB_OFF_COMMAND_H

#include <string>
#include "command.h"
#include "hottub.h"

class Hottub_Off_Command : public Command
{
public:
    Hottub_Off_Command(Hottub &hottub);
    virtual ~Hottub_Off_Command();

	virtual void execute();
	virtual void undo();
	virtual std::string to_string();

protected:
	Hottub &hottub_;
};

#endif /* HOTTUB_OFF_COMMAND_H */

