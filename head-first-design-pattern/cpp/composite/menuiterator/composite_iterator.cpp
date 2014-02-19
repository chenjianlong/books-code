/* $Id$ */

#include <typeinfo>
#include "composite_iterator.h"
#include "menu.h"

Composite_Iterator::Composite_Iterator(MENU_LIST &menus) : menus_(menus)
{ 
	it_ = menus_.begin();
}

Composite_Iterator::~Composite_Iterator()
{ }

Menu_Component* Composite_Iterator::next()
{
	if (!has_next()) {
		return NULL;
	}

	Menu_Component *component(NULL);
	if (!stack_.empty()) {
		component = stack_.top().get()->next();
	} else {
		component = (it_++)->get();
	}

	if (typeid(*component) == typeid(Menu)) {
		stack_.push(ITER_PTR(component->create_iterator()));
	}
	return component;
}

bool Composite_Iterator::has_next()
{
	if (stack_.empty() && it_ == menus_.end()) {
		return false;
	} else if (!stack_.empty()) {
		Iterator *it = stack_.top().get();
		if (!it->has_next()) {
			stack_.pop();
			return has_next();
		} else {
			return true;
		}
	} else {
		return true;
	}
}

