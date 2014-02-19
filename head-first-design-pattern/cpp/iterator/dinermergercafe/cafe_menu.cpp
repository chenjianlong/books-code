/* $Id$ */

#include <string>
#include "cafe_menu.h"
#include "menu_item.h"
#include "cafe_menu_iterator.h"

using std::string;

Cafe_Menu::Cafe_Menu()
{ 
	add_item("Veggie Burger and Air Fries",
		"Veggie burger on a whole wheat bun, lettuce, tomato, and fries",
		true, 3.99);
	add_item("Soup of the day",
		"A cup of the soup of the day, with a side salad",
		false, 3.69);
	add_item("Burrito",
		"A large burrito, with whole pinto beans, salsa, guacamole",
		true, 4.29);
}

Cafe_Menu::~Cafe_Menu()
{ }

void Cafe_Menu::add_item(string name, string description, bool vegetarian, double price)
{
	items_[name] = Menu_Item(name, description, vegetarian, price);
}

ITEM_MAP& Cafe_Menu::get_items()
{
	return items_;
}

Iterator* Cafe_Menu::create_iterator()
{
	return new Cafe_Menu_Iterator(items_);
}

