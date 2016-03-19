/// \file reactor_logging_server_adapter.h
/// \brief The Reactor_Logging_Server_Adapter class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-09

#ifndef REACTOR_LOGGING_SERVER_ADAPTER_H
#define REACTOR_LOGGING_SERVER_ADAPTER_H

#include "reactor_logging_server.h"
#include <ace/Service_Object.h>

template<class ACCEPTOR>
class Reactor_Logging_Server_Adapter: public ACE_Service_Object
{
public:
    virtual int init(int argc, ACE_TCHAR *argv[]);
    virtual int fini();

    virtual int info(ACE_TCHAR **, size_t) const;
    virtual int suspend();
    virtual int resume();

private:
    Reactor_Logging_Server<ACCEPTOR> *server_;
};

#include "reactor_logging_server_adapter.inl"

#endif /* !REACTOR_LOGGING_SERVER_ADAPTER_H */
// vim: set et ts=4 sts=4 sw=4:
