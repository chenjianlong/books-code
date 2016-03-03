#include "rt_thread_per_connection_logging_server.h"
#include <ace/Sched_Params.h>

int RT_Thread_Per_Connection_Logging_Server::open(u_short port)
{
    ACE_Sched_Params fifo_sched_params(
        ACE_SCHED_FIFO,
        ACE_Sched_Params::priority_min(ACE_SCHED_FIFO),
        ACE_SCOPE_PROCESS);

    if (ACE_OS::sched_params(fifo_sched_params) == -1) {
        if (errno == EPERM | errno == ENOTSUP) {
            ACE_DEBUG((LM_DEBUG,
                       "Warning: user's not superuser, so "
                       "we'll run in the time-shared class\n"));
        } else {
            ACE_ERROR_RETURN((LM_ERROR,
                              "%p\n", "ACE_OS::sched_params()"),
                              -1);
        }
    }

    return Thread_Per_Connection_Logging_Server::open(port);
}

int RT_Thread_Per_Connection_Logging_Server::handle_data(ACE_SOCK_Stream *logging_client)
{
    int prio = ACE_Sched_Params::next_priority(
        ACE_SCHED_FIFO,
        ACE_Sched_Params::priority_min(ACE_SCHED_FIFO),
        ACE_SCOPE_THREAD);
    ACE_OS::thr_setprio(prio);
    return Thread_Per_Connection_Logging_Server::handle_data(logging_client);
}
// vim: set et ts=4 sts=4 sw=4:
