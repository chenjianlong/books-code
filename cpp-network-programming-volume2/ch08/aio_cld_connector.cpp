#include "aio_cld_connector.h"
#include <ace/INET_Addr.h>
#include <ace/Proactor.h>
#include <iostream>

using namespace std;

int AIO_CLD_Connector::validate_connection(
    const ACE_Asynch_Connect::Result &result,
    const ACE_INET_Addr &remote, const ACE_INET_Addr&)
{
    cout << "AIO_CLD_Connector::validate_connection" << endl;
    remote_addr_ = remote;
    if (!result.success()) {
        ACE_Time_Value delay(retry_delay_);
        retry_delay_ *= 2;
        if (retry_delay_ > MAX_RETRY_DELAY)
            retry_delay_ = MAX_RETRY_DELAY;
        proactor()->schedule_timer(*this, 0, delay);
        cout << "Failed to validate_connection" << endl;
        return -1;
    }

    retry_delay_ = INITIAL_RETRY_DELAY;
    return 0;
}

int AIO_CLD_Connector::reconnect()
{
    cout << "AIO_CLD_Connector::reconnect" << endl;
    return connect(remote_addr_);
}

void AIO_CLD_Connector::handle_time_out(const ACE_Time_Value&, const void*)
{
    cout << "AIO_CLD_Connector::handle_time_out" << endl;
    connect(remote_addr_);
}

AIO_Output_Handler* AIO_CLD_Connector::make_handler()
{
    cout << "AIO_CLD_Connector::make_handler" << endl;
    return OUTPUT_HANDLER::instance();
}
// vim: set et ts=4 sts=4 sw=4:
