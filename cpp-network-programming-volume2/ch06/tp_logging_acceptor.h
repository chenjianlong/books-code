/// \file tp_logging_acceptor.h
/// \brief The Tp_Logging_Acceptor class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-14

#ifndef TP_LOGGING_ACCEPTOR_H
#define TP_LOGGING_ACCEPTOR_H

#include "logging_acceptor.h"
#include "tp_logging_handler.h"

class TP_Logging_Acceptor: public Logging_Acceptor
{
public:
    TP_Logging_Acceptor(ACE_Reactor *r = ACE_Reactor::instance()):
        Logging_Acceptor(r) {
    }

    virtual int handle_input(ACE_HANDLE) {
        TP_Logging_Handler *peer_handler = 0;
        ACE_NEW_RETURN(peer_handler, TP_Logging_Handler(reactor()), -1);
        if (acceptor_.accept(peer_handler->peer()) == -1) {
            delete peer_handler;
            return -1;
        } else if (peer_handler->open() == -1) {
            peer_handler->handle_close(ACE_INVALID_HANDLE, 0);
        }

        return 0;
    }
};

#endif /* !TP_LOGGING_ACCEPTOR_H */
// vim: set et ts=4 sts=4 sw=4:
