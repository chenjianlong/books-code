#include "ac_cld_acceptor.h"

int AC_CLD_Acceptor::make_svc_handler(AC_Input_Handler *&sh)
{
    sh = &input_handler_;
    return 0;
}

int AC_CLD_Acceptor::handle_close(ACE_HANDLE, ACE_Reactor_Mask)
{
    PARENT::handle_close();
    input_handler_.close();
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
