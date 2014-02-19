/*!
 * \file observer.h
 * \brief The Observer interface. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-29
 */
/* $Id$ */

#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
    Observer() { };
    virtual ~Observer() { };

	virtual void update(float temp, float humidity, float pressure) = 0;
};

#endif /* OBSERVER_H */

