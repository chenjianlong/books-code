#include "cld_acceptor.h"
#include "cld_handler.h"
#include <ace/SOCK_Stream.h>
#include <iostream>

using namespace std;

int CLD_Acceptor::open(CLD_Handler *handler,
                       const ACE_INET_Addr &local_addr,
                       ACE_Reactor *r)
{
    reactor(r);
    handler_ = handler;
    if (acceptor_.open(local_addr) == -1
            || reactor()->register_handler(
                this,ACE_Event_Handler::ACCEPT_MASK) == -1) {
        return -1;
    }

    return 0;
}

ACE_HANDLE CLD_Acceptor::get_handle() const
{
    return acceptor_.get_handle();
}

int CLD_Acceptor::handle_input(ACE_HANDLE)
{
    cout << "CLD_Acceptor::handle_input" << endl;
    ACE_SOCK_Stream peer_stream;
    if (acceptor_.accept(peer_stream) == -1) {
        return -1;
    } else if (reactor()->register_handler(
                peer_stream.get_handle(), handler_,
                ACE_Event_Handler::READ_MASK) == -1) {
        return -1;
    } else {
        return 0;
    }
}

int CLD_Acceptor::handle_close(ACE_HANDLE, ACE_Reactor_Mask)
{
    cout << "CLD_Acceptor::handle_close" << endl;
    acceptor_.close();
    handler_->close();
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
