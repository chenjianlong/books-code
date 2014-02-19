/*!
 * \file pizza.h
 * \brief The Pizza class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-04-30
 */
/* $Id$ */

#ifndef PIZZA_H
#define PIZZA_H

#include <vector>
#include <string>

class Pizza
{
public:
    Pizza();
    virtual ~Pizza();

	virtual void prepare();
	virtual void bake();
	virtual void cut();
	virtual void box();

	virtual std::string get_name();
	virtual std::string to_string();

protected:
	std::string name_;
	std::string dough_;
	std::string sauce_;
	std::vector<std::string> toppings_;
};

#endif /* PIZZA_H */

