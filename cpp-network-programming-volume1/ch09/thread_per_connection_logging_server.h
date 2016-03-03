/// \file thread_per_connection_logging_server.h
/// \brief The Thread_Per_Connection_Logging_Server class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-02

#ifndef THREAD_PER_CONNECTION_LOGGING_SERVER_H
#define THREAD_PER_CONNECTION_LOGGING_SERVER_H

#include <ace/SOCK_Stream.h>
#include <ace/Thread_Manager.h>
#include "logging_server.h"
#include "logging_handler.h"

class Thread_Per_Connection_Logging_Server: public Logging_Server
{
public:
    class Thread_Args {
    public:
        Thread_Args(Thread_Per_Connection_Logging_Server *lsp): this_(lsp) {
        }

        Thread_Per_Connection_Logging_Server *this_;
        ACE_SOCK_Stream logging_peer_;
    };

    virtual int run(int argc, char *argv[]);
    static void* run_svc(void *arg);

protected:
    virtual int handle_connections();
    virtual int handle_data(ACE_SOCK_Stream *client);
};

#endif /* !THREAD_PER_CONNECTION_LOGGING_SERVER_H */
// vim: set et ts=4 sts=4 sw=4:
