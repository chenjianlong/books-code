/*!
 * \file tuner.h
 * \brief The Tuner class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef TUNER_H
#define TUNER_H

#include <string>

class Amplifier;

class Tuner
{
public:
	Tuner(std::string description, Amplifier *amplifier);
	virtual ~Tuner();

	virtual void on();
	virtual void off();
	virtual void set_frequency(double frequency);
	virtual void set_AM();
	virtual void set_FM();
	virtual std::string to_string();

protected:
	std::string description_;
	Amplifier *amplifier_;
	double frequency_;
};

#endif /* TUNER_H */

