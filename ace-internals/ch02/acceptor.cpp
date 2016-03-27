#include "acceptor.h"
#include "handle_data.h"
#include <ace/Log_Msg.h>
#include <ace/Reactor.h>

int Acceptor::open(const ACE_UINT16 port)
{
    ACE_INET_Addr addr;
    addr.set(port, INADDR_ANY);
    if (acceptor_.open(addr) == -1) {
        ACE_DEBUG((LM_DEBUG, "accept open error\n"));
        return -1;
    }

    return reactor()->register_handler(this, ACE_Event_Handler::ACCEPT_MASK);
}

int Acceptor::handle_input(ACE_HANDLE)
{
    Handle_Data *handle_data = 0;
    ACE_NEW_RETURN(handle_data, Handle_Data(reactor()), -1);
    if (acceptor_.accept(handle_data->get_peer()) == -1) {
        ACE_DEBUG((LM_DEBUG, "accept handle input accept error!\n"));
        handle_data->handle_close();
        return -1;
    } else if (handle_data->open() == -1) {
        ACE_DEBUG((LM_DEBUG, "accept handle input open error!\n"));
        handle_data->handle_close();
        return -1;
    }

    ACE_DEBUG((LM_DEBUG, "accept handle input OK\n"));
    return 0;
}

int Acceptor::handle_close(ACE_HANDLE, ACE_Reactor_Mask)
{
    acceptor_.close();
    delete this;
    ACE_DEBUG((LM_DEBUG, "accept handle close OK!\n"));
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
