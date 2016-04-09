#include <ace/Event_Handler.h>
#include <ace/Signal.h>
#include <ace/Service_Config.h>
#include <ace/Log_Msg.h>
#include <ace/Reactor.h>
#include <ace/DLL_Manager.h>

class Signal_Handler: public ACE_Event_Handler
{
    virtual int handle_signal(int sig, siginfo_t*, ucontext*) {
        ACE_Service_Config::reconfig_occurred(1);
        ACE_DEBUG((LM_DEBUG,
                   "execute ACE signal handler for signal %d.\n", sig));
        return 0;
    }
};

int main(int argc, char *argv[])
{
    ACE_DLL_Manager::instance()->unload_policy(ACE_DLL_UNLOAD_POLICY_PER_PROCESS);
    if (ACE_Service_Config::open(argc, argv) == -1)
        ACE_ERROR_RETURN((LM_ERROR, "%p\n", "ACE_Service_Config::open"), -1);

    Signal_Handler handle;
    if (ACE_Reactor::instance()->register_handler(SIGINT, &handle) == -1) {
        ACE_DEBUG((LM_DEBUG, "register signal error.\n"));
        return -1;
    }

    return ACE_Reactor::run_event_loop();
}
// vim: set et ts=4 sts=4 sw=4:
