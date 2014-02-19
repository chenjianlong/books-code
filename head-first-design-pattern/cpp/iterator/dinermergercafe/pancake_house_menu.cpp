/* $Id$ */

#include <string>
#include "pancake_house_menu.h"
#include "pancake_house_menu_iterator.h"
#include "menu_item.h"

using std::string;

Pancake_House_Menu::Pancake_House_Menu()
{
	add_item("K&B's Pancake Breakfast", 
		"Pancakes with scrambled eggs, and toast", 
		true,
		2.99);

	add_item("Regular Pancake Breakfast", 
		"Pancakes with fried eggs, sausage", 
		false,
		2.99);

	add_item("Blueberry Pancakes",
		"Pancakes made with fresh blueberries",
		true,
		3.49);

	add_item("Waffles",
		"Waffles, with your choice of blueberries or strawberries",
		true,
		3.59);
}

Pancake_House_Menu::~Pancake_House_Menu()
{ }

void Pancake_House_Menu::add_item(string name, string description, bool vegetarian, double price)
{
	items_.push_back(Menu_Item(name, description, vegetarian, price));
}

Iterator* Pancake_House_Menu::create_iterator()
{
	return new Pancake_House_Menu_Iterator(items_);
}

string Pancake_House_Menu::to_string()
{
	return "Objectville Pancake House Menu";
}

ITEM_LIST& Pancake_House_Menu::get_menu_items()
{
	return items_;
}

