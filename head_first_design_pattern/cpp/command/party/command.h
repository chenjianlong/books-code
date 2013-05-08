/*!
 * \file command.h
 * \brief The Command interface. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-06
 */
/* $Id$ */

#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <vector>
#include <string>

class Command
{
public:
    Command() { };
    virtual ~Command() { };

	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual std::string to_string() = 0;
	friend std::ostream& operator<<(std::ostream &os, Command &cmd);
};

inline std::ostream& operator<<(std::ostream &os, Command &cmd)
{
	os << cmd.to_string();
	return os;
}

typedef std::vector<Command*> COMMANDS;

#endif /* COMMAND_H */

