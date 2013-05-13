/*!
 * \file pancake_house_menu.h
 * \brief The Pancake_House_Menu class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef PANCAKE_HOUSE_MENU_H
#define PANCAKE_HOUSE_MENU_H

#include <string>
#include <list>
#include "menu.h"
#include "common.h"

class Menu_Item;

class Pancake_House_Menu : public Menu
{
public:
	Pancake_House_Menu();
	virtual ~Pancake_House_Menu();

	virtual void add_item(std::string name, std::string description, bool vegetarian, double price);
	virtual ITEM_LIST& get_menu_items();
	virtual Iterator* create_iterator();
	virtual std::string to_string();

protected:
	ITEM_LIST items_;
};

#endif /* PANCAKE_HOUSE_MENU_H */

