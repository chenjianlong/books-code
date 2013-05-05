/* $Id$ */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "pizza.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::auto_ptr;

Pizza::Pizza()
{ }

Pizza::~Pizza()
{ }

void Pizza::bake()
{
    cout << "Bake for 25 minutes at 350" << endl;
}

void Pizza::cut()
{
    cout << "Cutting the pizza into diagonal slices" << endl;
}

void Pizza::box()
{
    cout << "Place pizza in official PizzaStore box" << endl;
}

void Pizza::set_name(const string &name)
{
    name_ = name;
}

const string &Pizza::get_name() const
{
    return name_;
}

string Pizza::to_string()
{
    string result;
    result = "---- " + name_ + " ----\n";
    if (dough_.get() != NULL) {
        result += dough_->to_string() + "\n";
    }
    if (sauce_.get() != NULL) {
        result += sauce_->to_string() + "\n";
    }
    if (cheese_.get() != NULL) {
        result += cheese_->to_string() + "\n";
    }
    if (veggies_.get() != NULL) {
        for (VEGGIES_VEC::iterator it = veggies_->begin(); it != veggies_->end(); it++) {
            result += (*it)->to_string() + "\n";
        }
    }
    if (clam_.get() != NULL) {
        result += clam_->to_string() + "\n";
    }
    if (pepperoni_.get() != NULL) {
        result += pepperoni_->to_string() + "\n";
    }
    return result;
}

