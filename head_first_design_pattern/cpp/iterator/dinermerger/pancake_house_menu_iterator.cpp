/* $Id$ */

#include "pancake_house_menu_iterator.h"
#include "menu_item.h"

Pancake_House_Menu_Iterator::Pancake_House_Menu_Iterator(ITEM_LIST &items) : items_(items)
{ 
	it_ = items_.begin();
}

Pancake_House_Menu_Iterator::~Pancake_House_Menu_Iterator()
{ }

Menu_Item* Pancake_House_Menu_Iterator::next()
{
	return &(*(it_++));
}

bool Pancake_House_Menu_Iterator::has_next()
{
	return it_ != items_.end();
}

