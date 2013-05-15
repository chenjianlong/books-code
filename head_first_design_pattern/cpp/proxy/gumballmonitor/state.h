/*!
 * \file state.h
 * \brief The State interface.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-14
 */
/* $Id$ */

#ifndef STATE_H
#define STATE_H

#include <string>

class State
{
public:
	State() { };
	virtual ~State() { };

	virtual void insert_quarter() = 0;
	virtual void eject_quarter() = 0;
	virtual void turn_crank() = 0;
	virtual void dispense() = 0;
	virtual std::string to_string() = 0;
};

#endif /* STATE_H */

