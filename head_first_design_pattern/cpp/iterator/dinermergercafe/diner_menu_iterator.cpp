/* $Id$ */

#include "diner_menu_iterator.h"
#include "menu_item.h"

Diner_Menu_Iterator::Diner_Menu_Iterator(Menu_Item *items, unsigned int len) : items_(items), len_(len), position_(0)
{ }

Diner_Menu_Iterator::~Diner_Menu_Iterator()
{ }

Menu_Item* Diner_Menu_Iterator::next()
{
	return &(items_[position_++]);
}

bool Diner_Menu_Iterator::has_next()
{
	return position_ < len_;
}

