/*!
 * \file common.h
 * \brief The common definition.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-14
 */
/* $Id$ */

#ifndef COMMON_H
#define COMMON_H

#include <boost/shared_ptr.hpp>
#include <vector>
#include <memory>
#include <stack>

class Menu_Component;
class Iterator;

typedef typename boost::shared_ptr<Menu_Component> MENU;
typedef typename std::vector<MENU> MENU_LIST;
typedef typename boost::shared_ptr<Iterator> ITER_PTR;
typedef typename std::stack<ITER_PTR> ITER_STACK;

#endif /* COMMON_H */

