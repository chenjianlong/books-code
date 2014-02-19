/*!
 * \file duck.h
 * \brief The Duck class implementation.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-12
 */
/* $Id$ */

#ifndef DUCK_H
#define DUCK_H

#include <string>

class Duck
{
public:
	Duck(std::string name, int weight);
	virtual ~Duck();


	std::string to_string();
	int operator<(const Duck &right) const;
protected:
	std::string name_;
	int weight_;
};

#endif /* DUCK_H */

