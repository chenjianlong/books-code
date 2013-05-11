/* $Id$ */

#include <iostream>
#include <memory>
#include "duck_test_drive.h"
#include "turkey_adapter.h"
#include "mallard_duck.h"
#include "wild_turkey.h"

using std::cout;
using std::endl;
using std::auto_ptr;

Duck_Test_Drive::Duck_Test_Drive()
{ }

Duck_Test_Drive::~Duck_Test_Drive()
{ }

int Duck_Test_Drive::main(int argc, char *argv[])
{
	auto_ptr<Mallard_Duck> duck(new Mallard_Duck());
	auto_ptr<Wild_Turkey> turkey(new Wild_Turkey());
	auto_ptr<Duck> turkey_adapter(new Turkey_Adapter(turkey.get()));

	cout << "The Turkey says..." << endl;
	turkey->gobble();
	turkey->fly();

	cout << "\nThe Duck says..." << endl;
	test_duck(duck.get());

	cout << "\nThe TurkeyAdapter says..." << endl;
	test_duck(turkey_adapter.get());

	return 0;
}

void Duck_Test_Drive::test_duck(Duck *duck)
{
	duck->quack();
	duck->fly();
}

