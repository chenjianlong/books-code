#include "cld_connector.h"
#include "cld_handler.h"
#include <ace/SOCK_Connector.h>
#include <ace/OS_NS_unistd.h>

int CLD_Connector::connect(CLD_Handler *handler,
                           const ACE_INET_Addr &remote_addr)
{
    ACE_SOCK_Connector connector;

    if (connector.connect(handler->peer(), remote_addr) == -1) {
        return -1;
    } else if (handler->open(this) == -1) {
        handler->handle_close();
        return -1;
    }

    handler_ = handler;
    remote_addr_ = remote_addr;
    return 0;
}

int CLD_Connector::reconnect()
{
    const size_t MAX_RETRIES = 5;

    ACE_SOCK_Connector connector;
    ACE_Time_Value timeout(1);
    size_t i;
    for (i = 0; i < MAX_RETRIES; ++i) {
        if (i > 0) {
            ACE_OS::sleep(timeout);
        }

        if (connector.connect(handler_->peer(), remote_addr_, &timeout) == -1) {
            timeout *= 2;
        } else {
            int bufsiz = ACE_DEFAULT_MAX_SOCKET_BUFSIZ;
            handler_->peer().set_option(
                SOL_SOCKET, SO_SNDBUF, &bufsiz, sizeof(bufsiz));
            break;
        }
    }

    return i == MAX_RETRIES ? -1 : 0;
}
// vim: set et ts=4 sts=4 sw=4:
