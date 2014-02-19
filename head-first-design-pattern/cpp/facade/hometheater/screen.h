/*!
 * \file screen.h
 * \brief The Screen class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef SCREEN_H
#define SCREEN_H

#include <string>

class Screen
{
public:
	Screen(std::string description);
	virtual ~Screen();
	
	virtual void up();
	virtual void down();
	virtual std::string to_string();

protected:
	std::string description_;
};

#endif /* SCREEN_H */

