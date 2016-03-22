#include <ace/SOCK_Acceptor.h>
#include <ace/Log_Msg.h>

int ACE_TMAIN(int, ACE_TCHAR *[])
{
    ACE_INET_Addr port_to_listen(60000);
    ACE_SOCK_Acceptor acceptor;
    if (acceptor.open(port_to_listen, 1) == -1) {
        ACE_ERROR_RETURN((LM_ERROR,
                          ACE_TEXT("%p\n"),
                          ACE_TEXT("acceptor.open")),
                          -1);
    }

    while (true) {
        ACE_SOCK_Stream peer;
        ACE_INET_Addr peer_addr;
        if (acceptor.accept(peer, &peer_addr) == -1) {
            ACE_DEBUG((LM_DEBUG, ACE_TEXT("accept error!\n")));
        } else {
            ACE_TCHAR peer_name[MAXHOSTNAMELEN];
            peer_addr.addr_to_string(peer_name, MAXHOSTNAMELEN);
            ACE_DEBUG((LM_DEBUG, ACE_TEXT("Connection from %s\n"), peer_name));

            char buffer[4097];
            ssize_t bytes_received;
            while ((bytes_received = peer.recv(buffer, sizeof(buffer) - 1)) > 0) {
                buffer[bytes_received] = 0;
                ACE_DEBUG((LM_DEBUG, ACE_TEXT("recevier data: %s\n"), buffer));
            }

            peer.close();
            ACE_DEBUG((LM_DEBUG, ACE_TEXT("close the socket.\n")));
        }
    }

    ACE_NOTREACHED(return 0);
}
// vim: set et ts=4 sts=4 sw=4:
