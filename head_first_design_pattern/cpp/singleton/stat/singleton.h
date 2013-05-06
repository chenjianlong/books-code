/*!
 * \file singleton.h
 * \brief The Singleton class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-05
 */
/* $Id$ */

#ifndef SINGLETON_H
#define SINGLETON_H

class Singleton
{
public:
    static volatile Singleton *get_instance();

private:
    Singleton();
    virtual ~Singleton();

private:
    volatile static Singleton *unique_;
};

#endif /* SINGLETON_H */

