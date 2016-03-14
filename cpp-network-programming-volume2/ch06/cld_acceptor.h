/// \file cld_acceptor.h
/// \brief The Cld_Acceptor class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-14

#ifndef CLD_ACCEPTOR_H
#define CLD_ACCEPTOR_H

#include <ace/Event_Handler.h>
#include <ace/Reactor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/INET_Addr.h>

class CLD_Handler;

class CLD_Acceptor: public ACE_Event_Handler
{
public:
    /// \brief Initialization hook method.
    virtual int open(CLD_Handler*, const ACE_INET_Addr&,
                     ACE_Reactor* = ACE_Reactor::instance());

    virtual int handle_input(ACE_HANDLE handle);
    virtual int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE,
                             ACE_Reactor_Mask = 0);
    virtual ACE_HANDLE get_handle() const;

protected:
    ACE_SOCK_Acceptor acceptor_;

    CLD_Handler *handler_;
};

#endif /* !CLD_ACCEPTOR_H */
// vim: set et ts=4 sts=4 sw=4:
