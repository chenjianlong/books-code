#include "handle_data.h"

int Handle_Data::open()
{
    ACE_INET_Addr remote_addr;
    get_peer().get_remote_addr(remote_addr);
    ACE_DEBUG((LM_DEBUG,
               "the remote addr is %s\n",
               remote_addr.get_host_addr()));

    int ret = reactor()->register_handler(this, ACE_Event_Handler::READ_MASK);
    if (ret != -1) {
        ACE_DEBUG((LM_DEBUG, "handle data register OK!\n"));
    }

    return ret;
}

int Handle_Data::handle_input(ACE_HANDLE)
{
    char buf[513] = {0};
    int len = get_peer().recv(buf, 512);

    if (len > 0) {
        buf[len] = 0;
        ACE_DEBUG((LM_DEBUG, "recv data %s, len: %d\n", buf, len));
        return 0;
    } else if (len == 0) {
        ACE_DEBUG((LM_DEBUG, "recv data len is 0, client exit\n"));
    } else {
        ACE_DEBUG((LM_DEBUG, "recv data error: len < 0\n"));
        return -1;
    }

    return -1;
}

int Handle_Data::handle_close(ACE_HANDLE, ACE_Reactor_Mask)
{
    get_peer().close();
    ACE_DEBUG((LM_DEBUG, "handle data close.\n"));
    delete this;
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
