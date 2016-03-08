#include <ace/streams.h>
#include <ace/Reactor.h>
#include <ace/TP_Reactor.h>
#include <ace/Thread_Manager.h>
#include <ace/Auto_Ptr.h>
#include "logging_acceptor_ex.h"
#include "reactor_logging_server.h"
#include <string>
#include <iostream>

static ACE_THR_FUNC_RETURN event_loop(void *arg)
{
    ACE_Reactor *reactor = static_cast<ACE_Reactor*>(arg);

    reactor->owner(ACE_OS::thr_self());
    reactor->run_reactor_event_loop();
    return 0;
}

class Quit_Handler: public ACE_Event_Handler
{
public:
    Quit_Handler(ACE_Reactor *r): ACE_Event_Handler(r) {
    }

    virtual int handle_exception(ACE_HANDLE) {
        reactor()->end_reactor_event_loop();
        return -1;
    }

    virtual int handle_close(ACE_HANDLE, ACE_Reactor_Mask) {
        delete this;
        return 0;
    }

private:
    virtual ~Quit_Handler() {}
};

static ACE_THR_FUNC_RETURN controller(void *arg)
{
    ACE_Reactor *reactor = static_cast<ACE_Reactor*>(arg);
    Quit_Handler *quit_handler = 0;
    ACE_NEW_RETURN(quit_handler, Quit_Handler(reactor), 0);

    for (;;) {
        std::string user_input;
        std::getline(std::cin, user_input, '\n');
        if (user_input == "quit") {
            reactor->notify(quit_handler);
            break;
        }
    }

    return 0;
}

typedef Reactor_Logging_Server<Logging_Acceptor_Ex> Server_Logging_Daemon;

int main(int argc, char *argv[])
{
    const size_t N_THREADS = 4;
    ACE_TP_Reactor tp_reactor;
    ACE_Reactor reactor(&tp_reactor);
    ACE_Auto_Ptr<ACE_Reactor> delete_instance(ACE_Reactor::instance(&reactor));

    Server_Logging_Daemon *server = 0;
    ACE_NEW_RETURN(server, Server_Logging_Daemon(argc, argv, &reactor), 1);
    ACE_Thread_Manager::instance()->spawn_n(
        N_THREADS, event_loop, ACE_Reactor::instance());
    ACE_Thread_Manager::instance()->spawn(controller, ACE_Reactor::instance());
    return ACE_Thread_Manager::instance()->wait();
}
// vim: set et ts=4 sts=4 sw=4:
