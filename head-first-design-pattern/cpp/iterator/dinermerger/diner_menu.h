/*!
 * \file diner_menu.h
 * \brief The Diner_Menu class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef DINER_MENU_H
#define DINER_MENU_H

#include "menu.h"

class Menu_Item;

class Diner_Menu : public Menu
{
public:
	Diner_Menu();
	virtual ~Diner_Menu();

	virtual void add_item(std::string name, std::string description, bool Vegetarian, double price);
	virtual Menu_Item* get_menu_items();
	virtual Iterator* create_iterator();

protected:
	static const int MAX_ITEMS = 6;
	Menu_Item *menu_items_;
	int number_of_items_;
};

#endif /* DINER_MENU_H */

