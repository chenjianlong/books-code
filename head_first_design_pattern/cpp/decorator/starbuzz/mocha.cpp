/* $Id$ */

#include "mocha.h"

Mocha::Mocha(Beverage *beverage) : beverage_(beverage)
{ }

Mocha::~Mocha()
{
	if (beverage_) {
		delete beverage_;
		beverage_ = NULL;
	}
}

std::string Mocha::get_description()
{
	return beverage_->get_description() + ", Mocha";
}

double Mocha::cost()
{
	return 0.20 + beverage_->cost();
}

