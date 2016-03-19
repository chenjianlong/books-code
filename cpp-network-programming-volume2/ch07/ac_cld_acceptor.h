/// \file ac_cld_acceptor.h
/// \brief The AC_CLD_Acceptor class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-19

#ifndef AC_CLD_ACCEPTOR_H
#define AC_CLD_ACCEPTOR_H

#include "ac_input_handler.h"
#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>

class AC_CLD_Acceptor: public ACE_Acceptor<AC_Input_Handler, ACE_SOCK_Acceptor>
{
public:
    AC_CLD_Acceptor(AC_Output_Handler *handler = 0):
        output_handler_(handler), input_handler_(handler) {
    }

protected:
    typedef ACE_Acceptor<AC_Input_Handler, ACE_SOCK_Acceptor> PARENT;

    virtual int make_svc_handler(AC_Input_Handler *&sh);
    virtual int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE,
                             ACE_Reactor_Mask = 0);

    AC_Output_Handler *output_handler_;
    AC_Input_Handler input_handler_;
};

#endif /* !AC_CLD_ACCEPTOR_H */
// vim: set et ts=4 sts=4 sw=4:
