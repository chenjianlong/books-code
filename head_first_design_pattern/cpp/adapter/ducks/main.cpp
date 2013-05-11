/* $Id$ */

#include "turkey_test_drive.h"
#include "duck_test_drive.h"

int main(int argc, char *argv[])
{
	Duck_Test_Drive::main(argc, argv);
	return Turkey_Test_Drive::main(argc, argv);
}

