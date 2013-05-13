/*!
 * \file pancake_house_menu_iterator.h
 * \brief The Pancake_House_Menu_Iterator class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef PANCAKE_HOUSE_MENU_ITERATOR_H
#define PANCAKE_HOUSE_MENU_ITERATOR_H

#include <list>
#include "iterator.h"
#include "common.h"

class Pancake_House_Menu_Iterator : public Iterator
{
public:
	Pancake_House_Menu_Iterator(ITEM_LIST &items);
	virtual ~Pancake_House_Menu_Iterator();

	virtual Menu_Item* next();
	virtual bool has_next();

protected:
	ITEM_LIST &items_;
	ITEM_LIST::iterator it_;
};

#endif /* PANCAKE_HOUSE_MENU_ITERATOR_H */

