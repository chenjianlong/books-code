/* $Id$ */

#include <iostream>
#include <string>
#include <cctype>
#include "coffee_with_hook.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

Coffee_With_Hook::Coffee_With_Hook()
{ }

Coffee_With_Hook::~Coffee_With_Hook()
{ }

void Coffee_With_Hook::brew()
{
	cout << "Dripping Coffee through filter" << endl;
}

void Coffee_With_Hook::add_condiments()
{
	cout << "Adding Sugar and Milk" << endl;
}

bool Coffee_With_Hook::customer_wants_condiments()
{
	string answer = get_user_input();

	if (tolower(answer[0]) == 'y') {
		return true;
	} else {
		return false;
	}
}

string Coffee_With_Hook::get_user_input()
{
	string answer;

	cout << "Would you like milk and sugar with your coffee (y/n)? "; 

	cin >> answer;
	if (answer.empty()) {
		return "no";
	}
	return answer;
}

