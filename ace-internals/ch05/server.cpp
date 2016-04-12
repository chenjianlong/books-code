#include "server.h"
#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>

int Data_Handler::open(void *p)
{
    if (super_type::open(p) == -1) {
        return -1;
    }

    ACE_TCHAR peer_name[MAXHOSTNAMELEN];
    ACE_INET_Addr peer_addr;
    if (this->peer().get_remote_addr(peer_addr) == 0
            && peer_addr.addr_to_string(peer_name, MAXHOSTNAMELEN) == 0) {
        ACE_DEBUG((LM_DEBUG, "(%p|%t) Connection from %s\n", peer_name));
    }

    return 0;
}

int Data_Handler::handle_input(ACE_HANDLE)
{
    const size_t INPUT_SIZE = 4096;
    char buffer[INPUT_SIZE] = { 0 };
    ssize_t recv_cnt = this->peer().recv(buffer, sizeof(buffer) - 1);
    if (recv_cnt <= 0) {
        ACE_DEBUG((LM_DEBUG, "(%p|%t) Connection closed\n"));
        return -1;
    }

    buffer[recv_cnt] = '\0';
    ACE_DEBUG((LM_DEBUG, "recv data %s.\n", buffer));
    return 0;
}

int Data_Handler::handle_close(ACE_HANDLE h, ACE_Reactor_Mask mask)
{
    return super_type::handle_close(h, mask);
}

typedef ACE_Acceptor<Data_Handler, ACE_SOCK_ACCEPTOR> ClientAcceptor;

int ACE_TMAIN(int, ACE_TCHAR *[])
{
    ACE_INET_Addr port_to_listen(60000);
    ClientAcceptor acceptor;
    if (acceptor.open(port_to_listen,
                      ACE_Reactor::instance(),
                      ACE_NONBLOCK) == -1) {
        return 1;
    }

    ACE_Reactor::instance()->run_reactor_event_loop();
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
