/* $Id$ */

#include <iostream>
#include <memory>
#include "turkey_test_drive.h"
#include "mallard_duck.h"
#include "duck_adapter.h"

using std::cout;
using std::endl;
using std::auto_ptr;

Turkey_Test_Drive::Turkey_Test_Drive()
{ }

Turkey_Test_Drive::~Turkey_Test_Drive()
{ }

int Turkey_Test_Drive::main(int argc, char *argv[])
{
	auto_ptr<Mallard_Duck> duck(new Mallard_Duck());
	auto_ptr<Turkey> duck_adapter(new Duck_Adapter(duck.get()));

	for (int i = 0; i < 10; i++) {
		cout << "The DuckAdapter says..." << endl;
		duck_adapter->gobble();
		duck_adapter->fly();
	}

	return 0;
}

