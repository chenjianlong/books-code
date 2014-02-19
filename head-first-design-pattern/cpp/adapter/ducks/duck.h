/*!
 * \file duck.h
 * \brief The Duck interface.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef DUCK_H
#define DUCK_H

class Duck
{
public:
	Duck() { }
	virtual ~Duck() { }

	virtual void quack() = 0;
	virtual void fly() = 0;
};

#endif /* DUCK_H */

