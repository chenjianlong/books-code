/*!
 * \file composite_iterator.h
 * \brief The Composite_Iterator class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-14
 */
/* $Id$ */

#ifndef COMPOSITE_ITERATOR_H
#define COMPOSITE_ITERATOR_H

#include "iterator.h"
#include "common.h"

class Composite_Iterator : public Iterator
{
public:
	Composite_Iterator(MENU_LIST &menus);
	virtual ~Composite_Iterator();

	virtual bool has_next();
	virtual Menu_Component* next();

protected:
	ITER_STACK stack_;
	MENU_LIST &menus_;
	MENU_LIST::iterator it_;
};

#endif /* COMPOSITE_ITERATOR_H */

