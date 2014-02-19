/*!
 * \file waitress.h
 * \brief The Waitress class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef WAITRESS_H
#define WAITRESS_H

class Iterator;
class Pancake_House_Menu;
class Diner_Menu;

class Waitress
{
public:
	Waitress(Pancake_House_Menu &pancake_house_menu, Diner_Menu &diner_menu);
	virtual ~Waitress();
	
	virtual void print_menu();
	virtual void print_menu(Iterator *iterator);
	virtual void print_vegatarian_menu();
	virtual bool is_item_vegetarian(std::string name);
	virtual void print_vegatarian_menu(Iterator *iterator);

private:
	bool is_vegetarian(std::string name, Iterator *iterator);

protected:
	Pancake_House_Menu &pancake_house_menu_;
	Diner_Menu &diner_menu_;
};

#endif /* WAITRESS_H */

