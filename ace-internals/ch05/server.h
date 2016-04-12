/// \file server.h
/// \brief Acceptor Connector Demo
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-04-12

#ifndef SERVER_H
#define SERVER_H

#include <ace/Svc_Handler.h>
#include <ace/SOCK_Stream.h>
#include <ace/Synch_Traits.h>

class Data_Handler: public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
public:
    typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH> super_type;

    virtual int open(void * = 0);
    virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);
    virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);
};

#endif /* !SERVER_H */
// vim: set et ts=4 sts=4 sw=4:
