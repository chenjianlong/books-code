/// \file logging_acceptor.h
/// \brief The Logging_Acceptor class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-04

#ifndef LOGGING_ACCEPTOR_H
#define LOGGING_ACCEPTOR_H

#include "logging_handler2.h"
#include <ace/Event_Handler.h>
#include <ace/INET_Addr.h>
#include <ace/Log_Record.h>
#include <ace/Reactor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/SOCK_Stream.h>

class Logging_Acceptor: public ACE_Event_Handler
{
public:
    typedef ACE_INET_Addr PEER_ADDR;

    Logging_Acceptor(ACE_Reactor *r = ACE_Reactor::instance()):
        ACE_Event_Handler(r) {
    }

    /// \brief Initialization method.
    virtual int open(const ACE_INET_Addr &local_addr);

    /// \brief Called by a reactor when there's a new connection to accept.
    virtual int handle_input(ACE_HANDLE = ACE_INVALID_HANDLE);

    /// \brief Called when this object is destroyed, e.g., when it's
    ///        removed from a reactor.
    virtual int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE,
                             ACE_Reactor_Mask = 0);

    /// \brief Return the passive-mode socket's I/O handle.
    virtual ACE_HANDLE get_handle() const {
        return acceptor_.get_handle();
    }

    /// \brief Returns a reference to the underlying <acceptor_>.
    ACE_SOCK_Acceptor& acceptor() {
        return acceptor_;
    }

protected:
    virtual ~Logging_Acceptor() {}

protected:
    ACE_SOCK_Acceptor acceptor_;
};

#endif /* !LOGGING_ACCEPTOR_H */
// vim: set et ts=4 sts=4 sw=4:
