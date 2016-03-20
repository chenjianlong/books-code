/// \file ac_cld_connector.h
/// \brief The AC_CLD_Connector class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-19

#ifndef AC_CLD_CONNECTOR_H
#define AC_CLD_CONNECTOR_H

#include "ac_output_handler.h"
#include <ace/Connector.h>
#include <ace/SOCK_Connector.h>

class AC_CLD_Connector:
    public ACE_Connector<AC_Output_Handler, ACE_SOCK_Connector>
{
public:
    typedef ACE_Connector<AC_Output_Handler, ACE_SOCK_Connector> PARENT;

    AC_CLD_Connector(AC_Output_Handler *handler = 0): handler_(handler) {
    }

    virtual ~AC_CLD_Connector(void) {
    }

    virtual int open(ACE_Reactor *r = ACE_Reactor::instance(), int flags = 0);
    int reconnect();

protected:
    virtual int connect_svc_handler(AC_Output_Handler *svc_handler,
        const ACE_SOCK_Connector::PEER_ADDR &remote_addr,
        ACE_Time_Value *timeout,
        const ACE_SOCK_Connector::PEER_ADDR &local_addr,
        int reuse_addr, int flags, int perms);

    AC_Output_Handler *handler_;
    ACE_INET_Addr remote_addr_;
};

#endif /* !AC_CLD_CONNECTOR_H */
// vim: set et ts=4 sts=4 sw=4:
