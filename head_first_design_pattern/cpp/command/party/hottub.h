/*!
 * \file hottub.h
 * \brief The Hottub class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-06
 */
/* $Id$ */

#ifndef HOTTUB_H
#define HOTTUB_H

class Hottub
{
public:
    Hottub();
    virtual ~Hottub();

	void on();
	void off();
	void circulate();
	void jets_on();
	void jets_off();
	void set_temperature(int temperature);

protected:
	bool on_;
	int temperature_;
};

#endif /* HOTTUB_H */

