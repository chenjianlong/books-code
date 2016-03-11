/// \file server_shutdown.h
/// \brief The Server_Shutdown class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-10

#ifndef SERVER_SHUTDOWN_H
#define SERVER_SHUTDOWN_H

#include <ace/Service_Object.h>
#include <ace/Reactor.h>

class Server_Shutdown: public ACE_Service_Object
{
public:
    virtual int init(int, ACE_TCHAR *[]);
    virtual int fini();

private:
    ACE_Reactor *reactor_;
};

#endif /* !SERVER_SHUTDOWN_H */
// vim: set et ts=4 sts=4 sw=4:
