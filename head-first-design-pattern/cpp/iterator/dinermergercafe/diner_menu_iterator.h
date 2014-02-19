/*!
 * \file diner_menu_iterator.h
 * \brief The Diner_Menu_Iterator class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef DINER_MENU_ITERATOR_H
#define DINER_MENU_ITERATOR_H

#include "iterator.h"

class Diner_Menu_Iterator : public Iterator
{
public:
	Diner_Menu_Iterator(Menu_Item *items, unsigned int len);
	virtual ~Diner_Menu_Iterator();

	virtual Menu_Item* next();
	virtual bool has_next();

protected:
	Menu_Item *items_;
	unsigned int len_;
	unsigned int position_;
};

#endif /* DINER_MENU_ITERATOR_H */

