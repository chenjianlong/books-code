/* $Id$ */

#include <cstddef>
#include "null_iterator.h"

Null_Iterator::Null_Iterator()
{ }

Null_Iterator::~Null_Iterator()
{ }

bool Null_Iterator::has_next()
{
	return false;
}

Menu_Component* Null_Iterator::next()
{
	return NULL;
}

