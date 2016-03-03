#include "thread_per_connection_logging_server.h"
#include <ace/Auto_Ptr.h>

int Thread_Per_Connection_Logging_Server::run(int argc, char *argv[])
{
    if (this->open(argc > 1 ? atoi(argv[1]) : 0) == -1)
        return -1;

    for (;;) {
        if (wait_for_multiple_events() == -1) return -1;
        if (handle_connections() == -1) return -1;
    }

    return 0;
}

int Thread_Per_Connection_Logging_Server::handle_connections()
{
    ACE_Auto_Ptr<Thread_Args> thread_args(new Thread_Args(this));

    if (acceptor().accept(thread_args->logging_peer_) == -1)
        return -1;

    if (ACE_Thread_Manager::instance()->spawn(
            Thread_Per_Connection_Logging_Server::run_svc,
            static_cast<void*>(thread_args.get()),
            THR_DETACHED | THR_SCOPE_SYSTEM) == -1)
        return -1;

    thread_args.release();
    return 0;
}

void* Thread_Per_Connection_Logging_Server::run_svc(void *arg)
{
    ACE_Auto_Ptr<Thread_Args> thread_args(static_cast<Thread_Args*>(arg));
    thread_args->this_->handle_data(&thread_args->logging_peer_);
    thread_args->logging_peer_.close();
    return 0;
}

int Thread_Per_Connection_Logging_Server::handle_data(ACE_SOCK_Stream *client)
{
    ACE_FILE_IO log_file;
    make_log_file(log_file, client);

    client->disable(ACE_NONBLOCK);

    Logging_Handler logging_handler(log_file, *client);
    ACE_Thread_Manager *tm = ACE_Thread_Manager::instance();
    ACE_thread_t me = ACE_OS::thr_self();

    while (!tm->testcancel(me) && logging_handler.log_record() != -1)
        continue;

    log_file.close();
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
