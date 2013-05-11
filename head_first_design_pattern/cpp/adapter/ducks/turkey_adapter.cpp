/* $Id$ */

#include "turkey_adapter.h"
#include "turkey.h"

Turkey_Adapter::Turkey_Adapter(Turkey *turkey) : turkey_(turkey)
{ }

Turkey_Adapter::~Turkey_Adapter()
{ }

void Turkey_Adapter::quack()
{
	turkey_->gobble();
}

void Turkey_Adapter::fly()
{
	for (int i = 0; i < 5; i++) {
		turkey_->fly();
	}
}

