/* $Id$ */

#include <iostream>
#include <assert.h>
#include "remote_control.h"
#include "no_command.h"

using std::endl;

#define ASSERT_RANGE(slot) assert((slot) >= 0 && (slot) < MAX_SLOTS)

Remote_Control::Remote_Control() : no_command_(new No_Command()) 
{
	for (int i = 0; i < MAX_SLOTS; i++) {
		on_commands_.push_back(no_command_.get());
		off_commands_.push_back(no_command_.get());
	}
	undo_command_ = no_command_.get();
}

Remote_Control::~Remote_Control()
{ }

void Remote_Control::set_command(int slot, Command *on_command, Command *off_command)
{
	ASSERT_RANGE(slot);
	on_commands_[slot] = on_command;
	off_commands_[slot] = off_command;
}

void Remote_Control::on_button_pushed(int slot)
{
	ASSERT_RANGE(slot);
	if (on_commands_[slot] == NULL) {
		return;
	}
	on_commands_[slot]->execute();
	undo_command_ = on_commands_[slot];
}

void Remote_Control::off_button_pushed(int slot)
{
	ASSERT_RANGE(slot);
	if (off_commands_[slot] == NULL) {
		return;
	}
	off_commands_[slot]->execute();
	undo_command_ = off_commands_[slot];
}

void Remote_Control::undo_button_pushed()
{
	if (NULL == undo_command_) {
		return;
	}
	undo_command_->undo();
}

std::ostream& operator<<(std::ostream &os, Remote_Control &rc)
{
	os << "\n------ Remote Control ------\n";
	for (int i = 0; i < Remote_Control::MAX_SLOTS; i++) {
		os << "[slot " << i << "] " << *(rc.on_commands_)[i] << "    " << *(rc.off_commands_)[i] << "\n";
	}
	os << "[undo] " << rc.undo_command_;
	return os;
}

