/* $Id$ */

#include <string>
#include <iostream>
#include <memory>
#include "waitress.h"
#include "menu.h"
#include "menu_item.h"
#include "iterator.h"

using std::string;
using std::cout;
using std::endl;
using std::auto_ptr;

Waitress::Waitress(Menu &pancake_house_menu, 
		Menu &diner_menu, 
		Menu &cafe_menu) : 
	pancake_house_menu_(pancake_house_menu), 
	diner_menu_(diner_menu),
	cafe_menu_(cafe_menu)
{ }

Waitress::~Waitress()
{ }

void Waitress::print_menu()
{
	auto_ptr<Iterator> pancake_iterator(pancake_house_menu_.create_iterator());
	auto_ptr<Iterator> diner_iterator(diner_menu_.create_iterator());
	auto_ptr<Iterator> cafe_iterator(cafe_menu_.create_iterator());

	cout << "MENU\n----\nBREAKFAST" << endl;
	print_menu(pancake_iterator.get());

	cout << "\nLUNCH" << endl;
	print_menu(diner_iterator.get());

	cout << "\nDINNER" << endl;
	print_menu(cafe_iterator.get());
}

void Waitress::print_menu(Iterator *iterator)
{
	Menu_Item *menu_item(NULL);
	while (iterator->has_next()) {
		menu_item = iterator->next();
		cout << menu_item->get_name() << ", "
			<< menu_item->get_price() << " -- "
			<< menu_item->get_description() << endl;
	}
}

void Waitress::print_vegatarian_menu()
{
	auto_ptr<Iterator> pancake_iterator(pancake_house_menu_.create_iterator());
	print_vegatarian_menu(pancake_iterator.get());
	auto_ptr<Iterator> diner_iterator(diner_menu_.create_iterator());
	print_vegatarian_menu(diner_iterator.get());
	auto_ptr<Iterator> cafe_iterator(cafe_menu_.create_iterator());
	print_vegatarian_menu(cafe_iterator.get());
}

bool Waitress::is_item_vegetarian(string name)
{
	auto_ptr<Iterator> breakfast_iterator(pancake_house_menu_.create_iterator());
	if (is_vegetarian(name, breakfast_iterator.get())) {
		return true;
	}
	auto_ptr<Iterator> diner_iterator(diner_menu_.create_iterator());
	if (is_vegetarian(name, diner_iterator.get())) {
		return true;
	}
	auto_ptr<Iterator> cafe_iterator(diner_menu_.create_iterator());
	if (is_vegetarian(name, cafe_iterator.get())) {
		return true;
	}
	return false;
}

void Waitress::print_vegatarian_menu(Iterator *iterator)
{
	Menu_Item *item(NULL);
	while (iterator->has_next()) {
		item = iterator->next();
		if (item->is_vegetarian()) {
			cout << item->get_name()
				<< "\t\t" << item->get_price() << "\n"
				<< "\t" << item->get_description() << endl;
		}
	}
}

bool Waitress::is_vegetarian(string name, Iterator *iterator)
{
	Menu_Item *item(NULL);
	while (iterator->has_next()) {
		item = iterator->next();
		if (name == item->get_name() && item->is_vegetarian()) {
			return true;
		}
	}
	return false;
}

