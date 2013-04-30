/* $Id$ */

#include "soy.h"

Soy::Soy(Beverage *beverage) : beverage_(beverage)
{ }

Soy::~Soy()
{
	if (beverage_) {
		delete beverage_;
		beverage_ = NULL;
	}
}

std::string Soy::get_description()
{
	return beverage_->get_description() + ", Soy";
}

double Soy::cost()
{
	return 0.15 + beverage_->cost();
}

