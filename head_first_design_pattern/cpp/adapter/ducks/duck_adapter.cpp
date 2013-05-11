/* $Id$ */

#include <cstdlib>
#include "duck_adapter.h"
#include "duck.h"

Duck_Adapter::Duck_Adapter(Duck *duck) : duck_(duck)
{ }

Duck_Adapter::~Duck_Adapter()
{ }

void Duck_Adapter::gobble()
{
	duck_->quack();
}

void Duck_Adapter::fly()
{
	if (rand() % 5 == 0) {
		duck_->fly();
	}
}

