/*!
 * \file menu.h
 * \brief The Menu class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-13
 */
/* $Id$ */

#ifndef MENU_H
#define MENU_H

#include <string>
#include "menu_component.h"
#include "common.h"

class Menu : public Menu_Component
{
public:
	Menu(std::string name, std::string description);
	virtual ~Menu();

	virtual void add(Menu_Component *t);
	virtual void remove(int i);
	virtual Menu_Component* get_child(int i);
	virtual std::string get_name();
	virtual std::string get_description();
	virtual Iterator* create_iterator();
	virtual void print();

protected:
	MENU_LIST menus_;
	std::string name_;
	std::string description_;
};

#endif /* MENU_H */

