/*!
 * \file remote_control.h
 * \brief The Remote_Control class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-08
 */
/* $Id$ */

#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H

#include <iostream>
#include <memory>
#include "command.h"

class Remote_Control
{
public:
	enum { MAX_SLOTS = 7 };
    Remote_Control();
    virtual ~Remote_Control();

	void set_command(int slot, Command *on_command, Command *off_command);
	void on_button_pushed(int slot);
	void off_button_pushed(int slot);
	void undo_button_pushed();

	friend std::ostream& operator<<(std::ostream &os, Remote_Control &rc);

protected:
	COMMANDS on_commands_;
	COMMANDS off_commands_;
	Command *undo_command_;
	std::auto_ptr<Command> no_command_;
};

#endif /* REMOTE_CONTROL_H */

