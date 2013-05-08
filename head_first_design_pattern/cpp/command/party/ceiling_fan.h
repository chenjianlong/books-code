/*!
 * \file ceiling_fan.h
 * \brief The Ceiling_Fan class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-06
 */
/* $Id$ */

#ifndef CEILING_FAN_H
#define CEILING_FAN_H

#include <string>

class Ceiling_Fan
{
public:
	enum { HIGH = 3, MEDIUM = 2, LOW = 1, OFF = 0 };
    Ceiling_Fan(std::string location);
    virtual ~Ceiling_Fan();

	void high();
	void medium();
	void low();
	void off();
	int get_speed();

protected:
	std::string location_;
	int speed_;
};

#endif /* CEILING_FAN_H */

