/*!
 * \file gumball_monitor.h
 * \brief The Gumball_Monitor class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-15
 */
/* $Id$ */

#ifndef GUMBALL_MONITOR_H
#define GUMBALL_MONITOR_H

class Gumball_Machine;

class Gumball_Monitor
{
public:
	Gumball_Monitor(Gumball_Machine &machine);
	virtual ~Gumball_Monitor();

	virtual void report();

protected:
	Gumball_Machine &machine_;
};

#endif /* GUMBALL_MONITOR_H */

