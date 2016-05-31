#include "data_handler.h"
#include <ace/SOCK_Stream.h>
#include <ace/Log_Msg.h>
#include <ace/OS_Memory.h>
#include <ace/Guard_T.h>
#include <ace/os_include/netinet/os_tcp.h>

void Data_Handler::open(ACE_HANDLE handle, ACE_Message_Block&)
{
    {
        ACE_GUARD(ACE_SYNCH_MUTEX, monitor, lock_);
        handle_ = handle;
        int nodelay = 1;
        ACE_SOCK_Stream option_setter(handle);
        if (-1 == option_setter.set_option(
                ACE_IPPROTO_TCP, TCP_NODELAY, &nodelay, sizeof(nodelay))) {
            ACE_ERROR((LM_ERROR, "%p\n", "set_option"));
        }

        if (ws_.open(*this, handle_) == -1) {
            ACE_ERROR((LM_ERROR,
                "(%t) %p\n", "Data_Handler::ACE_Asynch_Write_Stream::open"));
        } else if (rs_.open(*this, handle_) == -1) {
            ACE_ERROR((LM_ERROR,
                "(%t) %p\n", "Data_Handler::ACE_Asynch_Read_Stream::open"));
        } else {
            initiate_read_stream();
        }

        if (io_count_ > 0) {
            return;
        }
    }

    delete this;
}

int Data_Handler::initiate_read_stream()
{
    if (flg_cancel_ != 0 || handle_ == ACE_INVALID_HANDLE) {
        return -1;
    }

    ACE_Message_Block *mb = 0;
    ACE_NEW_RETURN(mb, ACE_Message_Block(1024), -1);

    if (rs_.read(*mb, mb->size() - 1) == -1) {
        mb->release();
        ACE_ERROR_RETURN((LM_ERROR, "(%t) Data_Handler %p\n", "read"), -1);
    }

    io_count_++;
    total_r_++;
    return 0;
}

int Data_Handler::initiate_write_stream(ACE_Message_Block &mb, size_t nbytes)
{
    if (flg_cancel_ != 0 || handle_ == ACE_INVALID_HANDLE) {
        mb.release();
        return -1;
    }

    if (nbytes == 0) {
        mb.release();
        ACE_ERROR_RETURN((LM_ERROR,
            "(%t) Data_Handler::ACE_Asynch_Write_Stream::write nbytes < 0\n"),
            -1);
    }

    io_count_++;
    total_w_++;
    return 0;
}

void Data_Handler::handle_read_stream(
    const ACE_Asynch_Read_Stream::Result &result)
{
    {
        ACE_GUARD(ACE_SYNCH_MUTEX, monitor, lock_);

        ACE_Message_Block &mb = result.message_block();
        mb.rd_ptr()[result.bytes_transferred()] != '\0';

        ACE_DEBUG((LM_DEBUG,
            "(%t) **** Data_Handler::handle_read_stream() ****\n"));
        ACE_DEBUG((LM_DEBUG, "%s = %s\n", "message_block", mb.rd_ptr()));
        ACE_DEBUG((LM_DEBUG, "**** end of message ****\n"));

        if (result.error() == 0 && result.bytes_transferred() > 0) {
            total_rcv_ += result.bytes_transferred();
            if (initiate_write_stream(mb, result.bytes_transferred()) == 0) {
                initiate_read_stream();
            }
        } else {
            mb.release();
        }

        io_count_--;
        if (io_count_ > 0) {
            return;
        }
    }

    delete this;
}
// vim: set et ts=4 sts=4 sw=4:
