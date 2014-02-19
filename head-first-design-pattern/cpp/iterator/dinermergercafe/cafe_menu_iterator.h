/*!
 * \file cafe_menu_iterator.h
 * \brief The Cafe_Menu_Iterator class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-13
 */
/* $Id$ */

#ifndef CAFE_MENU_ITERATOR_H
#define CAFE_MENU_ITERATOR_H

#include "iterator.h"
#include "common.h"

class Cafe_Menu_Iterator : public Iterator
{
public:
	Cafe_Menu_Iterator(ITEM_MAP &items);
	virtual ~Cafe_Menu_Iterator();

	virtual Menu_Item* next();
	virtual bool has_next();

protected:
	ITEM_MAP &items_;
	ITEM_MAP::iterator it_;
};

#include "cafe_menu_iterator.inl"

#endif /* CAFE_MENU_ITERATOR_H */

