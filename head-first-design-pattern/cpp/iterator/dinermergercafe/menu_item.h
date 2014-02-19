/*!
 * \file menu_item.h
 * \brief The Menu_Item class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>

class Menu_Item
{
public:
	Menu_Item();
	Menu_Item(
			std::string name,
			std::string description,
			bool vegetarian,
			double price
			);
	virtual ~Menu_Item();

	virtual std::string get_name();
	virtual std::string get_description();
	virtual double get_price();
	virtual bool is_vegetarian();
	virtual std::string to_string();

protected:
	std::string name_;
	std::string description_;
	bool vegetarian_;
	double price_;
};

#endif /* MENU_ITEM_H */

