/* $Id$ */

#include <algorithm>
#include <iostream>
#include "duck_sort_test_drive.h"
#include "duck.h"

using std::cout;
using std::endl;
using std::sort;

#define ITEMS 6

Duck_Sort_Test_Drive::Duck_Sort_Test_Drive()
{ }

Duck_Sort_Test_Drive::~Duck_Sort_Test_Drive()
{ }

int Duck_Sort_Test_Drive::main(int argc, char *argv[])
{
	Duck ducks[ITEMS] = {
		Duck("Daffy" , 8),
		Duck("Dewey", 2),
		Duck("Howard", 7),
		Duck("Louie", 2),
		Duck("Donald", 10),
		Duck("Huey", 2)
	};

	cout << "Before sorting:" << endl;
	display(ducks);

	sort(ducks, ducks + ITEMS);

	cout << "\nAfter sorting:" << endl;
	display(ducks);

	return 0;
}

void Duck_Sort_Test_Drive::display(Duck ducks[])
{
	for (int i = 0; i < ITEMS; i++) {
		cout << ducks[i].to_string() << endl;
	}
}

