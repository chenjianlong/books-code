/*!
 * \file veggies.h
 * \brief The Veggies interface. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-02
 */
/* $Id$ */

#ifndef VEGGIES_H
#define VEGGIES_H

#include <boost/shared_ptr.hpp>
#include <vector>
#include <string>

class Veggies
{
public:
    Veggies() { };
    virtual ~Veggies() { };

    virtual std::string to_string() = 0;
};

typedef std::vector<boost::shared_ptr<Veggies> > VEGGIES_VEC;
typedef boost::shared_ptr<Veggies> VEGGIES_PTR;

#endif /* VEGGIES_H */

