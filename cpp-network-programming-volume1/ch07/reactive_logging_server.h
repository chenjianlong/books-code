/// \file reactive_logging_server.h
/// \brief The Reactive_Logging_Server class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-01-12

#ifndef REACTIVE_LOGGING_SERVER_H
#define REACTIVE_LOGGING_SERVER_H

#include <ace/Handle_Set.h>
#include "iterative_logging_server.h"

class Reactive_Logging_Server: public Iterative_Logging_Server
{
public:
    virtual int open(u_short logger_port);
    virtual int wait_for_multiple_events();
    virtual int handle_connections();
    virtual int handle_data(ACE_SOCK_Stream *);

private:
    ACE_Handle_Set master_handle_set_;
    ACE_Handle_Set active_handlers_;
};

#endif /* !REACTIVE_LOGGING_SERVER_H */
// vim: set et ts=4 sts=4 sw=4:
