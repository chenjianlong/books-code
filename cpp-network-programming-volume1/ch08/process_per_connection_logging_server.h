/// \file process_per_connection_logging_server.h
/// \brief The Process_Per_Connection_Logging_Server class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-02

#ifndef PROCESS_PER_CONNECTION_LOGGING_SERVER_H
#define PROCESS_PER_CONNECTION_LOGGING_SERVER_H

#include <ace/Log_Record.h>
#include <ace/Process.h>
#include <ace/Process_Manager.h>
#include <ace/Signal.h>
#include "logging_server.h"

class Process_Per_Connection_Logging_Server: public Logging_Server
{
public:
    virtual int run(int argc, char *argv[]);
    virtual int handle_connections();
    virtual int handle_data(ACE_SOCK_Stream *logging_peer);

private:
    int run_worker(int argc, char *argv[]);
    int run_master(int argc, char *argv[]);

private:
    char prog_name_[MAXPATHLEN + 1];
};

#endif /* !PROCESS_PER_CONNECTION_LOGGING_SERVER_H */
// vim: set et ts=4 sts=4 sw=4:
