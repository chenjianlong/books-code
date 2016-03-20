/// \file tpc_logging_acceptor.h
/// \brief The TPC_Logging_Acceptor class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-16

#ifndef TPC_LOGGING_ACCEPTOR_H
#define TPC_LOGGING_ACCEPTOR_H

#include "tpc_logging_handler.h"
#include <ace/SOCK_Acceptor.h>
#include <ace/Reactor.h>
#include <ace/Acceptor.h>

class TPC_Logging_Acceptor: public ACE_Acceptor<TPC_Logging_Handler, ACE_SOCK_Acceptor>
{
public:
    typedef ACE_Acceptor<TPC_Logging_Handler, ACE_SOCK_Acceptor> PARENT;
    typedef ACE_SOCK_Acceptor::PEER_ADDR PEER_ADDR;

    TPC_Logging_Acceptor(ACE_Reactor *r): PARENT(r) {
    }

    virtual ~TPC_Logging_Acceptor() {
    }

    virtual int open(const ACE_SOCK_Acceptor::PEER_ADDR &local_addr,
                     ACE_Reactor *reactor = ACE_Reactor::instance(),
                     int flags = 0, int use_select = 1, int reuse_addr = 1);

    virtual int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE,
        ACE_Reactor_Mask = ACE_Event_Handler::ALL_EVENTS_MASK);

    virtual int accept_svc_handler(TPC_Logging_Handler *sh);
};

#endif /* !TPC_LOGGING_ACCEPTOR_H */
// vim: set et ts=4 sts=4 sw=4:
