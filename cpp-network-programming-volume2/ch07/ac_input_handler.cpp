#include "ac_input_handler.h"
#include "ac_output_handler.h"
#include "logging_handler.h"
#include <ace/OS_NS_sys_socket.h>
#include <iostream>

using namespace std;

int AC_Input_Handler::handle_input(ACE_HANDLE handle)
{
    cout << "AC_Input_Handler::handle_input" << endl;
    ACE_Message_Block *mblk = 0;
    ACE_FILE_IO log_file;
    Logging_Handler logging_handler(log_file, handle);

    if (logging_handler.recv_log_record(mblk) != -1) {
        if (output_handler_->put(mblk->cont()) != -1) {
            mblk->cont(0);
            mblk->release();
            return 0;
        } else {
            mblk->release();
        }
    }

    return -1;
}

int AC_Input_Handler::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask)
{
    connected_clients_.clr_bit(handle);
    return ACE_OS::closesocket(handle);
}

int AC_Input_Handler::open(void*)
{
    ACE_HANDLE handle = peer().get_handle();
    if (reactor()->register_handler(
            handle, this, ACE_Event_Handler::READ_MASK) == -1)
        return -1;

    connected_clients_.set_bit(handle);
    return 0;
}

int AC_Input_Handler::close(u_long)
{
    ACE_Message_Block *shutdown_message = 0;
    ACE_NEW_RETURN(shutdown_message,
        ACE_Message_Block(0, ACE_Message_Block::MB_STOP), -1);
    output_handler_->put(shutdown_message);

    reactor()->remove_handler(connected_clients_, ACE_Event_Handler::READ_MASK);
    return output_handler_->wait();
}
// vim: set et ts=4 sts=4 sw=4:
