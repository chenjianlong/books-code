/*!
 * \file turkey.h
 * \brief The Turkey interface.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef TURKEY_H
#define TURKEY_H

class Turkey
{
public:
	Turkey() { }
	virtual ~Turkey() { }

	virtual void gobble() = 0;
	virtual void fly() = 0;
};

#endif /* TURKEY_H */

