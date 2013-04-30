/* $Id$ */

#include "milk.h"

Milk::Milk(Beverage *beverage) : beverage_(beverage)
{ }

Milk::~Milk()
{
	if (beverage_) {
		delete beverage_;
		beverage_ = NULL;
	}
}

std::string Milk::get_description()
{
	return beverage_->get_description() + ", Milk";
}

double Milk::cost()
{
	return 0.10 + beverage_->cost();
}

