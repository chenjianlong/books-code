/// \file aio_client_logging_daemon.h
/// \brief The Aio_Client_Logging_Daemon class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-20

#ifndef AIO_CLIENT_LOGGING_DAEMON_H
#define AIO_CLIENT_LOGGING_DAEMON_H

#include "aio_cld_acceptor.h"
#include <ace/Task.h>

class AIO_Client_Logging_Daemon: public ACE_Task<ACE_NULL_SYNCH>
{
public:
    virtual int init(int argc, ACE_TCHAR *argv[]);
    virtual int fini();
    virtual int svc();

protected:
    ACE_INET_Addr cld_addr_;
    ACE_INET_Addr sld_addr_;
    AIO_CLD_Acceptor acceptor_;
};

#endif /* !AIO_CLIENT_LOGGING_DAEMON_H */
// vim: set et ts=4 sts=4 sw=4:
