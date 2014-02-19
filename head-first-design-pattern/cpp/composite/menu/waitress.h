/*!
 * \file waitress.h
 * \brief The Waitress class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-13
 */
/* $Id$ */

#ifndef WAITRESS_H
#define WAITRESS_H

class Menu_Component;

class Waitress
{
public:
	Waitress(Menu_Component &all_menus);
	virtual ~Waitress();

	virtual void print_menu();

protected:
	Menu_Component &all_menus_;
};

#endif /* WAITRESS_H */

