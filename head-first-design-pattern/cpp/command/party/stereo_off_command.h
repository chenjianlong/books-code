/*!
 * \file stereo_off_command.h
 * \brief The Stereo_Off_Command class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-08
 */
/* $Id$ */

#ifndef STEREO_OFF_COMMAND_H
#define STEREO_OFF_COMMAND_H

#include <string>
#include "command.h"
#include "stereo.h"

class Stereo_Off_Command : public Command
{
public:
    Stereo_Off_Command(Stereo &stereo);
    virtual ~Stereo_Off_Command();

	virtual void execute();
	virtual void undo();
	virtual std::string to_string();

protected:
	Stereo &stereo_;
};

#endif /* STEREO_OFF_COMMAND_H */

