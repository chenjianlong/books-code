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
class Menu;

class Waitress
{
public:
	Waitress(Menu &pancake_house_menu, Menu &diner_menu, Menu &cafe_menu);
	virtual ~Waitress();
	
	virtual void print_menu();
	virtual void print_menu(Iterator *iterator);
	virtual void print_vegatarian_menu();
	virtual bool is_item_vegetarian(std::string name);
	virtual void print_vegatarian_menu(Iterator *iterator);

private:
	bool is_vegetarian(std::string name, Iterator *iterator);

protected:
	Menu &pancake_house_menu_;
	Menu &diner_menu_;
	Menu &cafe_menu_;
};

#endif /* WAITRESS_H */

