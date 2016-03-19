#include "ac_output_handler.h"
#include "ac_cld_connector.h"
#include <ace/OS_NS_sys_time.h>
#include <ace/Signal.h>
#include <iostream>

using namespace std;

int AC_Output_Handler::put(ACE_Message_Block *mb, ACE_Time_Value *timeout)
{
    int result;
    while ((result = putq(mb, timeout)) == -1) {
        if (msg_queue()->state() != ACE_Message_Queue_Base::PULSED)
            break;
    }

    return result;
}

int AC_Output_Handler::open(void *connector)
{
    connector_ = static_cast<AC_CLD_Connector*>(connector);
    int bufsiz = ACE_DEFAULT_MAX_SOCKET_BUFSIZ;
    peer().set_option(SOL_SOCKET, SO_SNDBUF, &bufsiz, sizeof(bufsiz));
    if (reactor()->register_handler(this, ACE_Event_Handler::READ_MASK) == -1)
        return -1;

    if (msg_queue()->activate() == ACE_Message_Queue_Base::ACTIVATED) {
        msg_queue()->high_water_mark(QUEUE_MAX);
        return activate(THR_SCOPE_SYSTEM);
    } else {
        return 0;
    }
}

int AC_Output_Handler::svc()
{
    ACE_Message_Block *chunk[ACE_IOV_MAX];
    size_t message_index = 0;
    ACE_Time_Value time_of_last_send(ACE_OS::gettimeofday());
    ACE_Time_Value timeout;
    ACE_Sig_Action no_sigpipe((ACE_SignalHandler) SIG_IGN);
    ACE_Sig_Action original_action;
    no_sigpipe.register_action(SIGPIPE, &original_action);

    for (;;) {
        if (message_index == 0) {
            timeout = ACE_OS::gettimeofday();
            timeout += FLUSH_TIMEOUT;
        }

        ACE_Message_Block *mblk = 0;
        if (getq(mblk, &timeout) == -1) {
            if (errno == ESHUTDOWN) {
                if (connector_->reconnect() == -1) {
                    break;
                }

                continue;
            } else if (errno != EWOULDBLOCK) {
                break;
            } else if (message_index == 0) {
                continue;
            }
        } else {
            if (mblk->size() == 0
                    && mblk->msg_type() == ACE_Message_Block::MB_STOP) {
                mblk->release();
                break;
            }

            chunk[message_index] = mblk;
            ++message_index;
        }

        if (message_index >= ACE_IOV_MAX
                || (ACE_OS::gettimeofday() - time_of_last_send >=
                    ACE_Time_Value(FLUSH_TIMEOUT))) {
            if (send(chunk, message_index) == -1)
                break;

            time_of_last_send = ACE_OS::gettimeofday();
        }
    }

    if (message_index > 0)
        send(chunk, message_index);

    no_sigpipe.restore_action(SIGPIPE, original_action);
    return 0;
}

int AC_Output_Handler::send(ACE_Message_Block *chunk[], size_t &count)
{
    cout << "AC_Output_Handler::send, count=" << count << endl;
    iovec iov[ACE_IOV_MAX];
    size_t iov_size;
    int result = 0;

    for (iov_size = 0; iov_size < count; ++iov_size) {
        iov[iov_size].iov_base = chunk[iov_size]->rd_ptr();
        iov[iov_size].iov_len = chunk[iov_size]->length();
    }

    while (peer().sendv_n(iov, iov_size) == -1) {
        if (connector_->reconnect() == -1) {
            result = -1;
            break;
        }
    }

    while (iov_size > 0) {
        chunk[--iov_size]->release();
        chunk[iov_size] = 0;
    }

    count = iov_size;
    cout << "AC_Output_Handler::send, after send count=" << count << endl;
    return result;
}

int AC_Output_Handler::handle_input(ACE_HANDLE h)
{
    peer().close();
    reactor()->remove_handler(h,
        ACE_Event_Handler::READ_MASK | ACE_Event_Handler::DONT_CALL);
    msg_queue()->pulse();
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
