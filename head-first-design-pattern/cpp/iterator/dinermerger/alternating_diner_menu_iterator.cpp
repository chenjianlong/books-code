/* $Id$ */

#include <ctime>
#include "alternating_diner_menu_iterator.h"
#include "menu_item.h"

Alternating_Diner_Menu_Iterator::Alternating_Diner_Menu_Iterator(Menu_Item *list, unsigned int len) : list_(list), len_(len), position_(0)
{ 
	time_t t = time(NULL);
	tm *time_ptr = localtime(&t);
	position_ = time_ptr->tm_wday % 2;
}

Alternating_Diner_Menu_Iterator::~Alternating_Diner_Menu_Iterator()
{ }

Menu_Item* Alternating_Diner_Menu_Iterator::next()
{
	Menu_Item *menu_item = &(list_[position_]);
	position_ += 2;
	return menu_item;
}

bool Alternating_Diner_Menu_Iterator::has_next()
{
	return position_ < len_;
}

std::string Alternating_Diner_Menu_Iterator::to_string()
{
	return "Alternating Diner Menu Iterator";
}

