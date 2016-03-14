/// \file cld_connector.h
/// \brief The CLD_Connector class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-14

#ifndef CLD_CONNECTOR_H
#define CLD_CONNECTOR_H

#include <ace/INET_Addr.h>

class CLD_Handler;

class CLD_Connector
{
public:
    int connect(CLD_Handler *handler, const ACE_INET_Addr &remote_addr);
    int reconnect();

private:
    CLD_Handler *handler_;
    ACE_INET_Addr remote_addr_;
};

#endif /* !CLD_CONNECTOR_H */
// vim: set et ts=4 sts=4 sw=4:
