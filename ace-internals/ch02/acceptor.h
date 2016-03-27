/// \file acceptor.h
/// \brief The Acceptor class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-22

#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <ace/Event_Handler.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Reactor.h>

class Acceptor: public ACE_Event_Handler
{
public:
    Acceptor(ACE_Reactor *r = ACE_Reactor::instance()): ACE_Event_Handler(r) {
    }

    int open(const ACE_UINT16 port);
    int handle_input(ACE_HANDLE = ACE_INVALID_HANDLE);
    int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE, ACE_Reactor_Mask = 0);

    ACE_HANDLE get_handle() const {
        return acceptor_.get_handle();
    }

    ACE_SOCK_Acceptor &get_acceptor() {
        return acceptor_;
    }

private:
    virtual ~Acceptor() {
    }

private:
    ACE_SOCK_Acceptor acceptor_;
};

#endif /* !ACCEPTOR_H */
// vim: set et ts=4 sts=4 sw=4:
