#include "logging_acceptor_ex.h"
#include "logging_event_handler_ex.h"

int Logging_Acceptor_Ex::handle_input(ACE_HANDLE)
{
    Logging_Event_Handler_Ex *peer_handler = 0;
    ACE_NEW_RETURN(peer_handler, Logging_Event_Handler_Ex(reactor()), -1);
    if (acceptor_.accept(peer_handler->peer()) == -1) {
        delete peer_handler;
        return -1;
    } else if (peer_handler->open() == -1) {
        peer_handler->handle_close();
        return -1;
    }

    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
