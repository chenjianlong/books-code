#include "tss_thread_per_connection_logging_server.h"
#include <ace/Signal.h>
#include <ace/OS_NS_sys_time.h>
#include <ace/Time_Value.h>

static void sigterm_handler(int)
{
}

int main(int argc, char *argv[])
{
    ACE_Sig_Action sa(sigterm_handler, SIGTERM);

    TSS_Thread_Per_Connection_Logging_Server server;
    if (server.run(argc, argv) == -1 && errno != EINTR)
        ACE_ERROR_RETURN((LM_ERROR, "%p\n", "server.run()"), -1);

    ACE_Thread_Manager::instance()->cancel_all();

    ACE_Time_Value timeout(ACE_OS::gettimeofday());
    timeout += 60;
    return ACE_Thread_Manager::instance()->wait(&timeout);
}
// vim: set et ts=4 sts=4 sw=4:
