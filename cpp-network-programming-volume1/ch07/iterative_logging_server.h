/// \file iterative_logging_server.h
/// \brief Iterative Logging Server
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-01-07

#ifndef ITERATIVE_LOGGING_SERVER_H
#define ITERATIVE_LOGGING_SERVER_H

#include <ace/FILE_IO.h>
#include <ace/INET_Addr.h>
#include <ace/Log_Msg.h>
#include "logging_server.h"
#include "logging_handler.h"

class Iterative_Logging_Server: public Logging_Server
{
public:
    Iterative_Logging_Server();
    virtual ~Iterative_Logging_Server();

    Logging_Handler& logging_handler() {
        return logging_handler_;
    }

protected:
    virtual int open(u_short logger_port);
    virtual int handle_connections();
    virtual int handle_data(ACE_SOCK_Stream*);

private:
    ACE_FILE_IO log_file_;
    Logging_Handler logging_handler_;
};

#endif /* !ITERATIVE_LOGGING_SERVER_H */
// vim: set et ts=4 sts=4 sw=4:
