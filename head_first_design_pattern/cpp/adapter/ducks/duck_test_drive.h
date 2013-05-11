/*!
 * \file duck_test_drive.h
 * \brief The Duck_Test_Drive class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-11
 */
/* $Id$ */

#ifndef DUCK_TEST_DRIVE_H
#define DUCK_TEST_DRIVE_H

class Duck;

class Duck_Test_Drive
{
public:
	Duck_Test_Drive();
	virtual ~Duck_Test_Drive();

	static int main(int argc, char *argv[]);
	static void test_duck(Duck *duck);
};

#endif /* DUCK_TEST_DRIVE_H */

