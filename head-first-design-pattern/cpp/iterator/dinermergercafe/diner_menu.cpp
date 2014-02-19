/* $Id$ */

#include <iostream>
#include "diner_menu.h"
#include "menu_item.h"
#include "diner_menu_iterator.h"

using std::cout;
using std::endl;

Diner_Menu::Diner_Menu() : menu_items_(NULL), number_of_items_(0)
{
	menu_items_ = new Menu_Item[MAX_ITEMS];
	add_item("Vegetarian BLT",
		"(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
	add_item("BLT",
		"Bacon with lettuce & tomato on whole wheat", false, 2.99);
	add_item("Soup of the day",
		"Soup of the day, with a side of potato salad", false, 3.29);
	add_item("Hotdog",
		"A hot dog, with saurkraut, relish, onions, topped with cheese",
		false, 3.05);
	add_item("Steamed Veggies and Brown Rice",
		"Steamed vegetables over brown rice", true, 3.99);
	add_item("Pasta",
		"Spaghetti with Marinara Sauce, and a slice of sourdough bread",
		true, 3.89);
}

Diner_Menu::~Diner_Menu()
{ 
	if (menu_items_) {
		delete [] menu_items_;
		menu_items_ = NULL;
	}
}

void Diner_Menu::add_item(std::string name, std::string description, bool Vegetarian, double price)
{
	if (number_of_items_ >= MAX_ITEMS) {
		cout << "Sorry, menu is full!  Can't add item to menu" << endl;
	} else {
		menu_items_[number_of_items_++] = Menu_Item(name, description, Vegetarian, price);
	}
}

Menu_Item* Diner_Menu::get_menu_items()
{
	return menu_items_;
}

Iterator* Diner_Menu::create_iterator()
{
	return new Diner_Menu_Iterator(menu_items_, MAX_ITEMS);
}

