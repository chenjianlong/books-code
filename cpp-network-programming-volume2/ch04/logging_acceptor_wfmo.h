/// \file logging_acceptor_wfmo.h
/// \brief The Logging_Acceptor_WFMO class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-08

#ifndef LOGGING_ACCEPTOR_WFMO_H
#define LOGGING_ACCEPTOR_WFMO_H

#include "logging_acceptor_ex.h"
#include "logging_event_handler_wfmo.h"

class Logging_Acceptor_WFMO: public Logging_Acceptor_Ex
{
public:
    Logging_Acceptor_WFMO(ACE_Reactor *r):
        Logging_Acceptor_Ex(r) {
    }

protected:
    virtual int handle_input(ACE_HANDLE h) {
        Logging_Event_Handler_WFMO *peer_handler = 0;
        ACE_NEW_RETURN(
            peer_handler,
            Logging_Event_Handler_WFMO(reactor()), -1);
        if (acceptor_.accept(peer_handler->peer()) == -1) {
            delete peer_handler;
            return -1;
        } else if (peer_handler->open() == -1) {
            peer_handler->handle_close();
            return -1;
        }

        return 0;
    }

protected:
    ACE_Thread_Mutex lock_;
};

#endif /* !LOGGING_ACCEPTOR_WFMO_H */
// vim: set et ts=4 sts=4 sw=4:
