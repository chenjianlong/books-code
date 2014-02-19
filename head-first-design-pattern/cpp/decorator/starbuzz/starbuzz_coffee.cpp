/* $Id$ */

#include <iostream>
#include <string>
#include "starbuzz_coffee.h"
#include "espresso.h"
#include "dark_roast.h"
#include "house_blend.h"
#include "beverage.h"
#include "mocha.h"
#include "whip.h"
#include "soy.h"

Starbuzz_Coffee::Starbuzz_Coffee()
{ }

Starbuzz_Coffee::~Starbuzz_Coffee()
{ }

int Starbuzz_Coffee::main(int argc, char *argv[])
{
	using namespace std;

	Beverage *beverage = new Espresso();
	cout << beverage->get_description() << " $" << beverage->cost() << endl;
	delete beverage;

	Beverage *beverage2 = new Dark_Roast();
	beverage2 = new Mocha(beverage2);
	beverage2 = new Mocha(beverage2);
	beverage2 = new Whip(beverage2);
	cout << beverage2->get_description() << " $" << beverage2->cost() << endl;
	delete beverage2;

	Beverage *beverage3 = new House_Blend();
	beverage3 = new Soy(beverage3);
	beverage3 = new Mocha(beverage3);
	beverage3 = new Whip(beverage3);
	cout << beverage3->get_description() << " $" << beverage3->cost() << endl;
	delete beverage3;

	return 0;
}

