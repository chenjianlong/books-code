/// \file aio_cld_connector.h
/// \brief The AIO_CLD_Connector class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-20

#ifndef AIO_CLD_CONNECTOR_H
#define AIO_CLD_CONNECTOR_H

#include "aio_output_handler.h"
#include <ace/Asynch_Connector.h>
#include <ace/Proactor.h>

class AIO_CLD_Connector:public ACE_Asynch_Connector<AIO_Output_Handler>
{
public:
    enum { INITIAL_RETRY_DELAY = 3, MAX_RETRY_DELAY = 60 };

    AIO_CLD_Connector(): retry_delay_(INITIAL_RETRY_DELAY) {
        open();
    }

    virtual int validate_connection(const ACE_Asynch_Connect::Result &result,
                                    const ACE_INET_Addr &remote,
                                    const ACE_INET_Addr &local);
    virtual int reconnect();
    virtual void handle_time_out(const ACE_Time_Value&, const void*);

protected:
    virtual AIO_Output_Handler* make_handler();

    ACE_INET_Addr remote_addr_;
    int retry_delay_;
};

typedef ACE_Unmanaged_Singleton<AIO_CLD_Connector, ACE_Null_Mutex> CLD_CONNECTOR;

#endif /* !AIO_CLD_CONNECTOR_H */
// vim: set et ts=4 sts=4 sw=4:
