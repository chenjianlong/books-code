/*!
 * \file subject.h
 * \brief The Subject interface. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-29
 */
/* $Id$ */

#ifndef SUBJECT_H
#define SUBJECT_H

class Observer;

class Subject
{
public:
    Subject() { };
    virtual ~Subject() { };
	
	virtual void register_observer(Observer *o) = 0;
	virtual void remove_observer(Observer *o) = 0;
	virtual void notify_observers() = 0;
};

#endif /* SUBJECT_H */

