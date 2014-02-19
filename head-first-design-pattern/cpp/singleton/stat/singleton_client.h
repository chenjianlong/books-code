/*!
 * \file singleton_client.h
 * \brief The Singleton_Client class implementation. 
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-05-05
 */
/* $Id$ */

#ifndef SINGLETON_CLIENT_H
#define SINGLETON_CLIENT_H

class Singleton_Client
{
public:
    Singleton_Client();
    virtual ~Singleton_Client();

    static int main(int argc, char *argv[]);
};

#endif /* SINGLETON_CLIENT_H */

