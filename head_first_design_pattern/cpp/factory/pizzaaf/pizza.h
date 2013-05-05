/*!
 * \file pizza.h
 * \brief The Pizza class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef PIZZA_H
#define PIZZA_H

#include <memory>
#include <string>
#include "dough.h"
#include "sauce.h"
#include "cheese.h"
#include "clams.h"
#include "pepperoni.h"
#include "veggies.h"

class Pizza
{
public:
    Pizza();
    virtual ~Pizza();

    virtual void prepare() = 0;
    virtual void bake();
    virtual void cut();
    virtual void box();

    virtual void set_name(const std::string &name);
    virtual const std::string& get_name() const;
    virtual std::string to_string();

protected:
    std::string name_;

    std::auto_ptr<Dough> dough_;
    std::auto_ptr<Sauce> sauce_;
    std::auto_ptr<VEGGIES_VEC> veggies_;
    std::auto_ptr<Cheese> cheese_;
    std::auto_ptr<Pepperoni> pepperoni_;
    std::auto_ptr<Clams> clam_;
};

#endif /* PIZZA_H */

