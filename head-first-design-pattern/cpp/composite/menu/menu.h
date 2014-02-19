/*!
 * \file menu.h
 * \brief The Menu class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-13
 */
/* $Id$ */

#ifndef MENU_H
#define MENU_H

#include <boost/shared_ptr.hpp>
#include <vector>
#include <string>
#include "menu_component.h"

class Menu : public Menu_Component
{
public:
	typedef boost::shared_ptr<Menu_Component> MENU;
	typedef std::vector<MENU> MENU_LIST;
	Menu(std::string name, std::string description);
	virtual ~Menu();

	virtual void add(Menu_Component *t);
	virtual void remove(int i);
	virtual Menu_Component* get_child(int i);
	virtual std::string get_name();
	virtual std::string get_description();
	virtual void print();

protected:
	MENU_LIST menus_;
	std::string name_;
	std::string description_;
};

#endif /* MENU_H */

