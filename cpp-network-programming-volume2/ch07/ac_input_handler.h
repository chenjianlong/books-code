/// \file ac_input_handler.h
/// \brief The AC_Input_Handler class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-16

#ifndef AC_INPUT_HANDLER_H
#define AC_INPUT_HANDLER_H

#include <ace/Svc_Handler.h>
#include <ace/SOCK_Stream.h>
#include <ace/Handle_Set.h>

class AC_Output_Handler;

class AC_Input_Handler: public ACE_Svc_Handler<ACE_SOCK_Stream, ACE_NULL_SYNCH>
{
public:
    AC_Input_Handler(AC_Output_Handler *handler = 0):
        output_handler_(handler) {
    }

    virtual int open(void*);
    virtual int close(u_long = 0);

protected:
    virtual int handle_input(ACE_HANDLE handle);
    virtual int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE,
                             ACE_Reactor_Mask = 0);

    AC_Output_Handler *output_handler_;
    ACE_Handle_Set connected_clients_;
};

#endif /* !AC_INPUT_HANDLER_H */
// vim: set et ts=4 sts=4 sw=4:
