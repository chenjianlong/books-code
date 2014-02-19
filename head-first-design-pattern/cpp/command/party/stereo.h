/*!
 * \file stereo.h
 * \brief The Stereo class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-07
 */
/* $Id$ */

#ifndef STEREO_H
#define STEREO_H

#include <string>

class Stereo
{
public:
    Stereo(std::string location);
    virtual ~Stereo();

	void on();
	void off();
	void set_CD();
	void set_DVD();
	void set_radio();
	void set_volume(int volume);

protected:
	std::string location_;
};

#endif /* STEREO_H */

