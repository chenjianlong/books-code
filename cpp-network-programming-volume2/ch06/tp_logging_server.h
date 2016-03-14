/// \file tp_logging_server.h
/// \brief The Tp_Logging_Server class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-14

#ifndef TP_LOGGING_SERVER_H
#define TP_LOGGING_SERVER_H

#include "tp_logging_acceptor.h"
#include "reactor_logging_server.h"
#include <ace/Service_Object.h>

class TP_Logging_Server: public ACE_Service_Object
{
public:
    TP_Logging_Server(): logging_dispatcher_(0) {
    }

    virtual int init(int argc, ACE_TCHAR *argv[]);
    virtual int fini();

protected:
    typedef Reactor_Logging_Server<TP_Logging_Acceptor> LOGGING_DISPATCHER;

    LOGGING_DISPATCHER *logging_dispatcher_;
};

#endif /* !TP_LOGGING_SERVER_H */
// vim: set et ts=4 sts=4 sw=4:
