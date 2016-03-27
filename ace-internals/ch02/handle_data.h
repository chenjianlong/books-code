/// \file handle_data.h
/// \brief The Handle_Data class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-22

#ifndef HANDLE_DATA_H
#define HANDLE_DATA_H

#include <ace/Reactor.h>
#include <ace/Event_Handler.h>
#include <ace/SOCK_Stream.h>
#include <ace/Log_Msg.h>

class Handle_Data: public ACE_Event_Handler
{
public:
    Handle_Data(ACE_Reactor *r = ACE_Reactor::instance()):
        ACE_Event_Handler(r) {
    }

    int open();
    int handle_input(ACE_HANDLE = ACE_INVALID_HANDLE);
    int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE, ACE_Reactor_Mask = 0);

    ACE_HANDLE get_handle() const {
        return peer_.get_handle();
    }

    ACE_SOCK_Stream& get_peer() {
        return peer_;
    }

private:
    ~Handle_Data() {
        ACE_DEBUG((LM_DEBUG, "handle data dctor\n"));
    }

private:
    ACE_SOCK_Stream peer_;
};

#endif /* !HANDLE_DATA_H */
// vim: set et ts=4 sts=4 sw=4:
