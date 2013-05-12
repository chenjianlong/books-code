/* $Id$ */

#include <iostream>
#include <string>
#include <cctype>
#include "tea_with_hook.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

Tea_With_Hook::Tea_With_Hook()
{ }

Tea_With_Hook::~Tea_With_Hook()
{ }

void Tea_With_Hook::brew()
{
	cout << "Steeping the tea" << endl;
}

void Tea_With_Hook::add_condiments()
{
	cout << "Adding Lemon" << endl;
}

bool Tea_With_Hook::customer_wants_condiments()
{
	std::string answer = get_user_input();

	if (tolower(answer[0]) == 'y') {
		return true;
	} else {
		return false;
	}
}

string Tea_With_Hook::get_user_input()
{
	string answer;

	cout << "Would you linke lemon with your tea (y/n)? "; 
	cin >> answer;

	if (answer.empty()) {
		return "no";
	}
	return answer;
}

