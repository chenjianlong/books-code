/// \file logging_server.h
/// \brief Logging Server
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-01-07

#ifndef LOGGING_SERVER_H
#define LOGGING_SERVER_H

#include <ace/FILE_IO.h>
#include <ace/SOCK_Acceptor.h>

class ACE_SOCK_Stream;

class Logging_Server
{
public:
    virtual int run(int argc, char *argv[]);

protected:
    virtual int open(u_short logger_port = 0);
    virtual int wait_for_multiple_events() {
        return 0;
    }

    virtual int handle_connections() = 0;
    virtual int handle_data(ACE_SOCK_Stream* = 0) = 0;

    int make_log_file(ACE_FILE_IO&, ACE_SOCK_Stream* = 0);

    virtual ~Logging_Server() {
        acceptor_.close();
    }

    ACE_SOCK_Acceptor &acceptor() {
        return acceptor_;
    }

private:
    ACE_SOCK_Acceptor acceptor_;
};

#endif /* !LOGGING_SERVER_H */
// vim: set et ts=4 sts=4 sw=4:
