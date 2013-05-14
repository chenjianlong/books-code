/*!
 * \file menu_component.h
 * \brief The Menu_Component class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-13
 */
/* $Id$ */

#ifndef MENU_COMPONENT_H
#define MENU_COMPONENT_H

#include <string>

class Iterator;

class Menu_Component
{
public:
	Menu_Component();
	virtual ~Menu_Component();

	virtual void add(Menu_Component *t);
	virtual void remove(int i);
	virtual Menu_Component* get_child(int i);
	virtual std::string get_name();
	virtual std::string get_description();
	virtual double get_price();
	virtual bool is_vegetarian();
	virtual Iterator* create_iterator();
	virtual void print();
};

#endif /* MENU_COMPONENT_H */

