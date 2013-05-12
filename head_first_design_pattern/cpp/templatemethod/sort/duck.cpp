/* $Id$ */

#include <sstream>
#include "duck.h"

Duck::Duck(std::string name, int weight) : name_(name), weight_(weight)
{ }

Duck::~Duck()
{ }

std::string Duck::to_string()
{
	std::stringstream ss;
	ss << name_ << " weights " << weight_;
	return ss.str();
}

int Duck::operator<(const Duck &right) const
{
	return weight_ < right.weight_;
}

