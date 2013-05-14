/*!
 * \file gumball_machine.h
 * \brief The Gumball_Machine class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-14
 */
/* $Id$ */

#ifndef GUMBALL_MACHINE_H
#define GUMBALL_MACHINE_H

#include <string>

class Gumball_Machine
{
public:
	enum STATE { 
		SOLD_OUT = 0,
		NO_QUARTER = 1,
		HAS_QUARTER = 2,
		SOLD = 3 };
	Gumball_Machine(unsigned int count);
	virtual ~Gumball_Machine();

	virtual void insert_quarter();
	virtual void eject_quarter();
	virtual void turn_crank();
	virtual void dispense();
	virtual void refill(unsigned int num);
	virtual std::string to_string();

protected:
	STATE state_;
	unsigned int count_;
};

#endif /* GUMBALL_MACHINE_H */

