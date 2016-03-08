#include "logging_acceptor_wfmo.h"
#include "reactor_logging_server.h"
#include <ace/streams.h>
#include <ace/Reactor.h>
#include <ace/WFMO_Reactor.h>
#include <ace/Thread_Manager.h>
#include <ace/Manual_Event.h>
#include <string>
#include <iostream>
#include <cstring>

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
        SetConsoleMode(
            ACE_STDIN,
            ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
        if (reactor()->register_handler(this, quit_seen_.handle()) == -1
                || ACE_Event_Handler::register_stdin_handler(
                    this, r, ACE_Thread_Manager::instance()) == -1)
            r->end_reactor_event_loop();
    }

    virtual int handle_input(ACE_HANDLE h) {
        char user_input[BUFSIZ];
        DWORD count;
        if (!ReadFile(h, user_input, BUFSIZ, &count, 0))
            return -1;

        user_input[count] = '\0';
        if (strncmp(user_input, "quit", 4) == 0)
            return -1;

        return 0;
    }

    virtual int handle_exception(ACE_HANDLE) {
        reactor()->end_reactor_event_loop();
        return -1;
    }

    virtual int handle_close(ACE_HANDLE, ACE_Reactor_Mask) {
        quit_seen_.signal();
        return 0;
    }

    virtual int handle_signal(int, siginfo_t*, ucontext_t*) {
        reactor()->end_reactor_event_loop();
        return 0;
    }

    virtual ~Quit_Handler() {
        ACE_Event_Handler::remove_stdin_handler(
            reactor(), ACE_Thread_Manager::instance());
        reactor()->remove_handler(quit_seen_.handle(),
                                  ACE_Event_Handler::DONT_CALL);
    }

private:
    ACE_Manual_Event quit_seen_;
};

typedef Reactor_Logging_Server<Logging_Acceptor_WFMO> Server_Logging_Daemon;

int main(int argc, char *argv[])
{
    const size_t N_THREADS = 4;
    ACE_WFMO_Reactor wfmo_reactor;
    ACE_Reactor reactor(&wfmo_reactor);

    Server_Logging_Daemon *server = 0;
    ACE_NEW_RETURN(server, Server_Logging_Daemon(argc, argv, &reactor), 1);
    Quit_Handler quit_handler(&reactor);
    ACE_Thread_Manager::instance()->spawn_n(
        N_THREADS, event_loop, &reactor);
    return ACE_Thread_Manager::instance()->wait();
}
// vim: set et ts=4 sts=4 sw=4:
