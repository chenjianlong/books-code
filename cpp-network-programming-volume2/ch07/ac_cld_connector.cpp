#include "ac_cld_connector.h"
#include <iostream>

using namespace std;

int AC_CLD_Connector::open(ACE_Reactor *r, int flags)
{
    return PARENT::open(r, flags);
}

int AC_CLD_Connector::connect_svc_handler(AC_Output_Handler *svc_handler,
                                          const ACE_SOCK_Connector::PEER_ADDR &remote_addr,
                                          ACE_Time_Value *timeout,
                                          const ACE_SOCK_Connector::PEER_ADDR &local_addr,
                                          int reuse_addr, int flags, int perms)
{
    if (PARENT::connect_svc_handler(svc_handler, remote_addr,
                                    timeout, local_addr,
                                    reuse_addr, flags, perms) == -1)
        return -1;

    remote_addr_ = remote_addr;
    return 0;
}

int AC_CLD_Connector::reconnect()
{
    const size_t MAX_RETRIES = 5;
    ACE_Time_Value timeout(1);
    size_t i;
    for (i = 0; i < MAX_RETRIES; ++i) {
        ACE_Synch_Options options(ACE_Synch_Options::USE_TIMEOUT, timeout);
        if (i > 0) ACE_OS::sleep(timeout);
        if (connect(handler_, remote_addr_, options) == 0)
            break;

        timeout *= 2;
    }

    return i == MAX_RETRIES ? -1 : 0;
}
// vim: set et ts=4 sts=4 sw=4:

