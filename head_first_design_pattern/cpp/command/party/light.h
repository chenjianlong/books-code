/*!
 * \file light.h
 * \brief The Light class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-06
 */
/* $Id$ */

#ifndef LIGHT_H
#define LIGHT_H

#include <string>

class Light
{
public:
    Light(std::string location);
    virtual ~Light();

	void on();
	void off();
	void dim(int level);
	int get_level();

protected:
	std::string location_;
	int level_;
};

#endif /* LIGHT_H */

