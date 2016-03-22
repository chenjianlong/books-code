#include <ace/SOCK_Connector.h>
#include <ace/Log_Msg.h>

int ACE_TMAIN(int, ACE_TCHAR *[])
{
    int ret = 0;
    const char *ip = "127.0.0.1";
    u_short port = 60000;
    ACE_INET_Addr addr(port, ip);

    ACE_SOCK_Connector connector;
    ACE_SOCK_Stream peer;
    // for nonblock connect
    // ACE_Time_Value time(0, 500);
    // ret = connector.connect(peer, addr, &time);

    ret = connector.connect(peer, addr);
    if (ret == -1) {
        ACE_ERROR_RETURN((LM_ERROR,
                          ACE_TEXT("%p\n"),
                          ACE_TEXT("connect")),
                          -1);
    }

    peer.send_n("hello world!", 12);
    peer.close();
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
