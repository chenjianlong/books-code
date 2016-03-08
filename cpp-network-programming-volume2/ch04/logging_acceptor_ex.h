/// \file logging_acceptor_ex.h
/// \brief The Logging_Acceptor_Ex class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-06

#ifndef LOGGING_ACCEPTOR_EX_H
#define LOGGING_ACCEPTOR_EX_H

#include <ace/INET_Addr.h>
#include <ace/Reactor.h>
#include "logging_acceptor.h"

class Logging_Acceptor_Ex: public Logging_Acceptor
{
public:
    typedef ACE_INET_Addr PEER_ADDR;

    Logging_Acceptor_Ex(ACE_Reactor *r = ACE_Reactor::instance()):
        Logging_Acceptor(r) {
    }

    virtual int handle_input(ACE_HANDLE = ACE_INVALID_HANDLE);
};

#endif /* !LOGGING_ACCEPTOR_EX_H */
// vim: set et ts=4 sts=4 sw=4:
