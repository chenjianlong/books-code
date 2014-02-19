/*!
 * \file alternating_diner_menu_iterator.h
 * \brief The Alternating_Diner_Menu_Iterator class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef ALTERNATING_DINER_MENU_ITERATOR_H
#define ALTERNATING_DINER_MENU_ITERATOR_H

#include <string>
#include "iterator.h"

class Alternating_Diner_Menu_Iterator : public Iterator
{
public:
	Alternating_Diner_Menu_Iterator(Menu_Item *list, unsigned int len);
	virtual ~Alternating_Diner_Menu_Iterator();

	virtual Menu_Item* next();
	virtual bool has_next();
	virtual std::string to_string();

protected:
	Menu_Item *list_;
	unsigned int len_;
	unsigned int position_;
};

#endif /* ALTERNATING_DINER_MENU_ITERATOR_H */

