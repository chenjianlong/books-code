/// \file reactor_logging_server.h
/// \brief The Reactor_Logging_Server class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-06

#ifndef REACTOR_LOGGING_SERVER_H
#define REACTOR_LOGGING_SERVER_H

#include <ace/ACE.h>
#include <ace/Reactor.h>

template<class ACCEPTOR>
class Reactor_Logging_Server: public ACCEPTOR
{
public:
    Reactor_Logging_Server(int argc, char *argv[], ACE_Reactor *reactor):
        ACCEPTOR(reactor)
    {
        u_short logger_port = argc > 1 ? atoi(argv[1]) : 0;
        typename ACCEPTOR::PEER_ADDR server_addr;
        int result;

        if (logger_port != 0) {
            result = server_addr.set(logger_port, ACE_UINT32(INADDR_ANY));
        } else {
            result = server_addr.set("ace_logger", ACE_UINT32(INADDR_ANY));
        }

        if (result != -1) {
            result = ACCEPTOR::open(server_addr);
        }

        if (-1 == result) reactor->end_reactor_event_loop();
    }
};

#endif /* !REACTOR_LOGGING_SERVER_H */
// vim: set et ts=4 sts=4 sw=4:
