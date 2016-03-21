#include "logging_handler.h"
#include <ace/Message_Block.h>
#include <ace/CDR_Stream.h>
#include <ace/Log_Record.h>
#include <ace/Log_Msg.h>
#include <cstring>

int Logging_Handler::recv_log_record(ACE_Message_Block *&mblk)
{
    ACE_INET_Addr peer_addr;
    logging_peer_.get_remote_addr(peer_addr);
    mblk = new ACE_Message_Block(MAXHOSTNAMELEN + 1);
    memset(mblk->wr_ptr(), '\0', MAXHOSTNAMELEN + 1);
    peer_addr.get_host_name(mblk->wr_ptr(), MAXHOSTNAMELEN);
    mblk->wr_ptr(strlen(mblk->wr_ptr()) + 1);
    ACE_Message_Block *payload = new ACE_Message_Block(ACE_DEFAULT_CDR_BUFSIZE);
    ACE_CDR::mb_align(payload);

    if (logging_peer_.recv_n(payload->wr_ptr(), 8) == 8) {
        payload->wr_ptr(8);

        ACE_InputCDR cdr(payload);
        ACE_CDR::Boolean byte_order;
        cdr >> ACE_InputCDR::to_boolean(byte_order);
        cdr.reset_byte_order(byte_order);

        ACE_CDR::ULong length;
        cdr >> length;

        ACE_CDR::grow(payload, 8 + ACE_CDR::MAX_ALIGNMENT + length);
        if (logging_peer_.recv_n(payload->wr_ptr(), length) > 0) {
            payload->wr_ptr(length);
            mblk->cont(payload);
            return length;
        }
    }

    payload->release();
    mblk->release();
    payload = mblk = 0;
    return -1;
}

int Logging_Handler::write_log_record(ACE_Message_Block *mblk)
{
    if (log_file_.send_n(mblk) == -1) return -1;

    if (ACE::debug()) {
        ACE_InputCDR cdr(mblk->cont());
        ACE_CDR::Boolean byte_order;
        ACE_CDR::ULong length;
        cdr >> ACE_InputCDR::to_boolean(byte_order);
        cdr.reset_byte_order(byte_order);
        cdr >> length;
        ACE_Log_Record log_record;
        cdr >> log_record;
        log_record.print(mblk->rd_ptr(), ACE_Log_Msg::STDERR, stderr);
    }

    return mblk->total_length();
}

int Logging_Handler::log_record()
{
    ACE_Message_Block *mblk = 0;
    if (recv_log_record(mblk) == -1) {
        return -1;
    } else {
        int result = write_log_record(mblk);
        mblk->release();
        return result == -1 ? -1 : 0;
    }
}
// vim: set et ts=4 sts=4 sw=4:
