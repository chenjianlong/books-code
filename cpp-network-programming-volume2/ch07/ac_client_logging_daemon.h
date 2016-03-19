/// \file ac_client_logging_daemon.h
/// \brief The Ac_Client_Logging_Daemon class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-19

#ifndef AC_CLIENT_LOGGING_DAEMON_H
#define AC_CLIENT_LOGGING_DAEMON_H

#include "ac_cld_acceptor.h"
#include "ac_cld_connector.h"
#include <ace/Service_Object.h>

class AC_Client_Logging_Daemon: public ACE_Service_Object
{
public:
    AC_Client_Logging_Daemon(): acceptor_(&output_handler_), connector_(&output_handler_) {
    }

    virtual int init(int argc, ACE_TCHAR *argv[]);
    virtual int fini();

protected:
    AC_CLD_Acceptor acceptor_;
    AC_CLD_Connector connector_;
    AC_Output_Handler output_handler_;
};

#endif /* !AC_CLIENT_LOGGING_DAEMON_H */
// vim: set et ts=4 sts=4 sw=4:
