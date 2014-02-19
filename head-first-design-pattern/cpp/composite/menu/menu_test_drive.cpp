/* $Id$ */

#include <memory>
#include "menu_test_drive.h"
#include "menu.h"
#include "menu_item.h"
#include "waitress.h"

using std::auto_ptr;

Menu_Test_Drive::Menu_Test_Drive()
{ }

Menu_Test_Drive::~Menu_Test_Drive()
{ }

int Menu_Test_Drive::main(int argc, char *argv[])
{
	Menu_Component *pancake_house_menu = 
		new Menu("PANCAKE HOUSE MENU", "Breakfast");
	Menu_Component *diner_menu = 
		new Menu("DINER MENU", "Lunch");
	Menu_Component *cafe_menu = 
		new Menu("CAFE MENU", "Dinner");
	Menu_Component *dessert_menu = 
		new Menu("DESSERT MENU", "Dessert of course!");
	Menu_Component *coffee_menu = new Menu("COFFEE MENU", "Stuff to go with your afternoon coffee");

	auto_ptr<Menu_Component> all_menus(new Menu("ALL MENUS", "All menus combined"));

	all_menus->add(pancake_house_menu);
	all_menus->add(diner_menu);
	all_menus->add(cafe_menu);

	pancake_house_menu->add(new Menu_Item(
		"K&B's Pancake Breakfast", 
		"Pancakes with scrambled eggs, and toast", 
		true,
		2.99));
	pancake_house_menu->add(new Menu_Item(
		"Regular Pancake Breakfast", 
		"Pancakes with fried eggs, sausage", 
		false,
		2.99));
	pancake_house_menu->add(new Menu_Item(
		"Blueberry Pancakes",
		"Pancakes made with fresh blueberries, and blueberry syrup",
		true,
		3.49));
	pancake_house_menu->add(new Menu_Item(
		"Waffles",
		"Waffles, with your choice of blueberries or strawberries",
		true,
		3.59));

	diner_menu->add(new Menu_Item(
		"Vegetarian BLT",
		"(Fakin') Bacon with lettuce & tomato on whole wheat", 
		true, 
		2.99));
	diner_menu->add(new Menu_Item(
		"BLT",
		"Bacon with lettuce & tomato on whole wheat", 
		false, 
		2.99));
	diner_menu->add(new Menu_Item(
		"Soup of the day",
		"A bowl of the soup of the day, with a side of potato salad", 
		false, 
		3.29));
	diner_menu->add(new Menu_Item(
		"Hotdog",
		"A hot dog, with saurkraut, relish, onions, topped with cheese",
		false, 
		3.05));
	diner_menu->add(new Menu_Item(
		"Steamed Veggies and Brown Rice",
		"Steamed vegetables over brown rice", 
		true, 
		3.99));

	diner_menu->add(new Menu_Item(
		"Pasta",
		"Spaghetti with Marinara Sauce, and a slice of sourdough bread",
		true, 
		3.89));

	diner_menu->add(dessert_menu);

	dessert_menu->add(new Menu_Item(
		"Apple Pie",
		"Apple pie with a flakey crust, topped with vanilla icecream",
		true,
		1.59));

	dessert_menu->add(new Menu_Item(
		"Cheesecake",
		"Creamy New York cheesecake, with a chocolate graham crust",
		true,
		1.99));
	dessert_menu->add(new Menu_Item(
		"Sorbet",
		"A scoop of raspberry and a scoop of lime",
		true,
		1.89));

	cafe_menu->add(new Menu_Item(
		"Veggie Burger and Air Fries",
		"Veggie burger on a whole wheat bun, lettuce, tomato, and fries",
		true, 
		3.99));
	cafe_menu->add(new Menu_Item(
		"Soup of the day",
		"A cup of the soup of the day, with a side salad",
		false, 
		3.69));
	cafe_menu->add(new Menu_Item(
		"Burrito",
		"A large burrito, with whole pinto beans, salsa, guacamole",
		true, 
		4.29));

	cafe_menu->add(coffee_menu);

	coffee_menu->add(new Menu_Item(
		"Coffee Cake",
		"Crumbly cake topped with cinnamon and walnuts",
		true,
		1.59));
	coffee_menu->add(new Menu_Item(
		"Bagel",
		"Flavors include sesame, poppyseed, cinnamon raisin, pumpkin",
		false,
		0.69));
	coffee_menu->add(new Menu_Item(
		"Biscotti",
		"Three almond or hazelnut biscotti cookies",
		true,
		0.89));

	Waitress waitress(*all_menus);

	waitress.print_menu();

	return 0;
}
