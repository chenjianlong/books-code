#include "acceptor.h"
#include <ace/Reactor.h>
#include <ace/Log_Msg.h>

int main(int argc, char *argv[])
{
    ACE_UINT16 port = 0;
    if (argc < 2)
        return -1;

    port = ACE_OS::atoi(argv[1]);
    Acceptor *accept;
    ACE_NEW_RETURN(accept, Acceptor(ACE_Reactor::instance()), -1);
    if (accept->open(port) == -1) {
        accept->handle_close();
        ACE_DEBUG((LM_DEBUG, "main open error!\n"));
        return -1;
    }

    if (ACE_Reactor::run_event_loop() == -1) {
        accept->handle_close();
        ACE_DEBUG((LM_DEBUG, "main run event loop error!\n"));
        return -1;
    }

    accept->handle_close();
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
