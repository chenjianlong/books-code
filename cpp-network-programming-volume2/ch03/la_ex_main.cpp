#include "logging_acceptor_ex.h"
#include "reactor_logging_server.h"
#include <ace/Log_Msg.h>

typedef Reactor_Logging_Server<Logging_Acceptor_Ex> Server_Logging_Deamon;

int main(int argc, char *argv[])
{
    ACE_Reactor reactor;
    Server_Logging_Deamon *server = 0;
    ACE_NEW_RETURN(server, Server_Logging_Deamon(argc, argv, &reactor), 1);

    if (reactor.run_reactor_event_loop() == -1)
        ACE_ERROR_RETURN((LM_ERROR, "%p\n", "run_reactor_event_loop()"), 1);

    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
