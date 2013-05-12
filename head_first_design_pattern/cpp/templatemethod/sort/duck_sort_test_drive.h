/*!
 * \file duck_sort_test_drive.h
 * \brief The Duck_Sort_Test_Drive class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef DUCK_SORT_TEST_DRIVE_H
#define DUCK_SORT_TEST_DRIVE_H

class Duck;

class Duck_Sort_Test_Drive
{
public:
	Duck_Sort_Test_Drive();
	virtual ~Duck_Sort_Test_Drive();

	static int main(int argc, char *argv[]);
	static void display(Duck ducks[]);
};
#endif /* DUCK_SORT_TEST_DRIVE_H */

