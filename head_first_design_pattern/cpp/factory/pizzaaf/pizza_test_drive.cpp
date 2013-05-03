/* $Id$ */

#include <memory>
#include <iostream>
#include "pizza_test_drive.h"
#include "ny_pizza_store.h"
#include "chicago_pizza_store.h"

using std::auto_ptr;
using std::cout;
using std::endl;

Pizza_Test_Drive::Pizza_Test_Drive()
{ }

Pizza_Test_Drive::~Pizza_Test_Drive()
{ }

int Pizza_Test_Drive::main(int argc, char *argv[])
{
    auto_ptr<Pizza_Store> ny_store(new NY_Pizza_Store());
    auto_ptr<Pizza_Store> chicago_store(new Chicago_Pizza_Store());

    auto_ptr<Pizza> pizza(ny_store->order_pizza("cheese"));
    cout << "Ethan ordered a " << pizza->to_string() << endl;

    pizza.reset(chicago_store->order_pizza("cheese"));
    cout << "Joel ordered a " << pizza->to_string() << endl;

    pizza.reset(ny_store->order_pizza("clam"));
    cout << "Ethan ordered a " << pizza->to_string() << endl;

    pizza.reset(chicago_store->order_pizza("clam"));
    cout << "Joel ordered a " << pizza->to_string() << endl;

    pizza.reset(ny_store->order_pizza("pepperoni"));
    cout << "Ethan ordered a " << pizza->to_string() << endl; 

    pizza.reset(chicago_store->order_pizza("pepperoni"));
    cout << "Joel ordered a " << pizza->to_string() << endl;

    pizza.reset(ny_store->order_pizza("veggie"));
    cout << "Ethan ordered a " << pizza->to_string() << endl; 

    pizza.reset(chicago_store->order_pizza("veggie"));
    cout << "Joel ordered a " << pizza->to_string() << endl; 
    
    return 0;
}

