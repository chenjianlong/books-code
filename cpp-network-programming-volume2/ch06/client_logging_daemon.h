/// \file client_logging_daemon.h
/// \brief The Client_Logging_Daemon class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-14

#ifndef CLIENT_LOGGING_DAEMON_H
#define CLIENT_LOGGING_DAEMON_H

#include "cld_handler.h"
#include "cld_acceptor.h"
#include "cld_connector.h"
#include <ace/Service_Object.h>

class Client_Logging_Daemon: public ACE_Service_Object
{
public:
    virtual int init(int argc, ACE_TCHAR *argv[]);
    virtual int fini();

protected:
    CLD_Handler handler_;
    CLD_Acceptor acceptor_;
    CLD_Connector connector_;
};

#endif /* !CLIENT_LOGGING_DAEMON_H */
// vim: set et ts=4 sts=4 sw=4:
