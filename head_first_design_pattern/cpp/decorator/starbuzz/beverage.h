/*!
 * \file beverage.h
 * \brief The Beverage class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-30
 */
/* $Id$ */

#ifndef BEVERAGE_H
#define BEVERAGE_H

#include <string>

class Beverage
{
public:
	Beverage() : description_("Unknown Beverage") { }
	Beverage(std::string desc) : description_(desc) { }
    virtual ~Beverage() { };

	virtual std::string get_description() {
		return description_;
	}

	virtual double cost() = 0;

private:
	std::string description_;
};

#endif /* BEVERAGE_H */

