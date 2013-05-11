/*!
 * \file popcorn_popper.h
 * \brief The Popcorn_Popper class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef POPCORN_POPPER_H
#define POPCORN_POPPER_H

#include <string>

class Popcorn_Popper
{
public:
	Popcorn_Popper(std::string description);
	virtual ~Popcorn_Popper();

	virtual void on();
	virtual void off();
	virtual void pop();
	virtual std::string to_string();

protected:
	std::string description_;
};

#endif /* POPCORN_POPPER_H */

