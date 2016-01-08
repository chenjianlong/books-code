/// \file logging_client.h
/// \brief Logging Client
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-01-07

#ifndef LOGGING_CLIENT_H
#define LOGGING_CLIENT_H

#include <ace/OS.h>
#include <ace/CDR_Stream.h>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Stream.h>
#include <ace/Log_Record.h>
#include <ace/streams.h>

class Logging_Client
{
public:
    ~Logging_Client();

    int send(const ACE_Log_Record &log_record);
    ACE_SOCK_Stream& peer() {
        return logging_peer_;
    }

private:
    ACE_SOCK_Stream logging_peer_;
};

#endif /* !LOGGING_CLIENT_H */
// vim: set et ts=4 sts=4 sw=4:
