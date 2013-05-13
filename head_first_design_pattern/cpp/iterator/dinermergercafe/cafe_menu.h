/*!
 * \file cafe_menu.h
 * \brief The Cafe_Menu class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-13
 */
/* $Id$ */

#ifndef CAFE_MENU_H
#define CAFE_MENU_H

#include <map>
#include <string>
#include "menu.h"
#include "common.h"

class Menu_Item;

class Cafe_Menu : public Menu
{
public:
	Cafe_Menu();
	virtual ~Cafe_Menu();

	virtual void add_item(std::string name, std::string description, bool vegetarian, double price);
	ITEM_MAP& get_items();
	virtual Iterator* create_iterator();

protected:
	ITEM_MAP items_;
};

#endif /* CAFE_MENU_H */

