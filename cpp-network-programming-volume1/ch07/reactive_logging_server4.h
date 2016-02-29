/// \file reactive_logging_server.h
/// \brief The Reactive_Logging_Server class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-01-12

#ifndef REACTIVE_LOGGING_SERVER_H
#define REACTIVE_LOGGING_SERVER_H

#include <ace/ACE.h>
#include <ace/Handle_Set.h>
#include <ace/Hash_Map_Manager.h>
#include <ace/Synch.h>
#include "logging_server.h"
#include "logging_handler.h"

typedef ACE_Hash_Map_Manager<ACE_HANDLE,
                             ACE_FILE_IO*,
                             ACE_Null_Mutex> LOG_MAP;

class Reactive_Logging_Server_Ex: public Logging_Server
{
public:
    virtual int open(u_short logger_port);
    virtual int wait_for_multiple_events();
    virtual int handle_connections();
    virtual int handle_data(ACE_SOCK_Stream *);

private:
    LOG_MAP log_map_;

    ACE_Handle_Set master_handle_set_;
    ACE_Handle_Set active_read_handlers_;
};

#endif /* !REACTIVE_LOGGING_SERVER_H */
// vim: set et ts=4 sts=4 sw=4:
