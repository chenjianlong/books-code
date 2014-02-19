/*!
 * \file null_iterator.h
 * \brief The Null_Iterator class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-14
 */
/* $Id$ */

#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

#include "iterator.h"

class Null_Iterator : public Iterator
{
public:
	Null_Iterator();
	virtual ~Null_Iterator();
	
	virtual bool has_next();
	virtual Menu_Component* next();
};

#endif /* NULL_ITERATOR_H */

