/*!
 * \file iterator.h
 * \brief The Iterator interface.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef ITERATOR_H
#define ITERATOR_H

class Menu_Item;

class Iterator
{
public:
	Iterator() { };
	virtual ~Iterator() { };

	virtual bool has_next() = 0;
	virtual Menu_Item* next() = 0;
};

#endif /* ITERATOR_H */

