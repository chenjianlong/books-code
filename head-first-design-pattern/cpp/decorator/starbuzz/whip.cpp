/* $Id$ */

#include "whip.h"

Whip::Whip(Beverage *beverage) : beverage_(beverage)
{ }

Whip::~Whip()
{
	if (beverage_) {
		delete beverage_;
		beverage_ = NULL;
	}
}

std::string Whip::get_description()
{
	return beverage_->get_description() + ", Whip";
}

double Whip::cost()
{
	return 0.10 + beverage_->cost();
}

