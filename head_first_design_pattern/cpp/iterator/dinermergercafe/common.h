/*!
 * \file common.h
 * \brief The Common definition.
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-13
 */
/* $Id$ */

#ifndef COMMON_H
#define COMMON_H

#include <map>
#include <list>
#include <string>

class Menu_Item;

typedef std::map<std::string, Menu_Item> ITEM_MAP;

typedef std::list<Menu_Item> ITEM_LIST;

#endif /* COMMON_H */

