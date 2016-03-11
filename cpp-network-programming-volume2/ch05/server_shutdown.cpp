#include "server_shutdown.h"
#include "sldex_export.h"
#include <ace/Thread_Manager.h>
#include <iostream>

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

int Server_Shutdown::init(int, ACE_TCHAR *[])
{
    reactor_ = ACE_Reactor::instance();
    return ACE_Thread_Manager::instance()->spawn(
        controller, reactor_, THR_DETACHED);
}

int Server_Shutdown::fini()
{
    return 0;
}

ACE_FACTORY_DEFINE(SLDEX, Server_Shutdown)
// vim: set et ts=4 sts=4 sw=4:
