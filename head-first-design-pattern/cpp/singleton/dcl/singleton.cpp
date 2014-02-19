/* $Id$ */

#include <boost/thread/locks.hpp> 
#include "singleton.h"

volatile Singleton *Singleton::unique_(NULL);
LOCK Singleton::lock_;

Singleton::Singleton()
{ }

Singleton::~Singleton()
{ }

volatile Singleton *Singleton::get_instance()
{
    if (NULL == unique_) {
        boost::lock_guard<LOCK> guard(lock_);
        if (NULL == unique_) {
            unique_ = new Singleton();
        }
    }
    return unique_;
}

void Singleton::close()
{
    if (NULL != unique_) {
        boost::lock_guard<LOCK> guard(lock_);
        if (NULL != unique_) {
            delete unique_;
            unique_ = NULL;
        }
    }
}

