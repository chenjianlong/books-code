/*!
 * \file theater_lights.h
 * \brief The Theater_Lights class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef THEATER_LIGHTS_H
#define THEATER_LIGHTS_H

#include <string>

class Theater_Lights
{
public:
	Theater_Lights(std::string description);
	virtual ~Theater_Lights();

	virtual void on();
	virtual void off();
	virtual void dim(int level);
	virtual std::string to_string();

protected:
	std::string description_;
};

#endif /* THEATER_LIGHTS_H */

