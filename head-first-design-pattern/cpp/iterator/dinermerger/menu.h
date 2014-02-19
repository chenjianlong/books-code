/*!
 * \file menu.h
 * \brief The Menu interface.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef MENU_H
#define MENU_H

class Iterator;

class Menu
{
public:
	Menu() { };
	virtual ~Menu() { };

	virtual Iterator* create_iterator() = 0;
};

#endif /* MENU_H */

