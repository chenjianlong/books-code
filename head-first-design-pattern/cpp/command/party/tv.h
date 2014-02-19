/*!
 * \file tv.h
 * \brief The TV class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-06
 */
/* $Id$ */

#ifndef TV_H
#define TV_H

#include <string>

class TV
{
public:
    TV(std::string location);
    virtual ~TV();

	void on();
	void off();
	void set_input_channel();

protected:
	std::string location_;
	int channel_;
};

#endif /* TV_H */

