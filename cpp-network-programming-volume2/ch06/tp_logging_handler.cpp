#include "tp_logging_handler.h"
#include "tp_logging_task.h"
#include <ace/Message_Block.h>

int TP_Logging_Handler::handle_input(ACE_HANDLE)
{
    ACE_Message_Block *mblk = 0;
    if (logging_handler_.recv_log_record(mblk) != -1) {
        ACE_Message_Block *log_blk = 0;
        ACE_NEW_RETURN(log_blk, ACE_Message_Block(reinterpret_cast<char*>(this)), -1);
        log_blk->cont(mblk);
        ACE_GUARD_RETURN(ACE_Thread_Mutex, guard, lock_, -1);
        if (TP_LOGGING_TASK::instance()->put(log_blk) == -1) {
            log_blk->release();
            return -1;
        }

        ++queued_count_;
        return 0;
    }

    return -1;
}

int TP_Logging_Handler::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask mask)
{
    int close_now = 0;
    if (handle != ACE_INVALID_HANDLE) {
        ACE_GUARD_RETURN(ACE_Thread_Mutex, guard, lock_, -1);
        if (queued_count_ == 0) {
            close_now = 1;
        } else {
            deferred_close_ = 1;
        }
    } else {
        ACE_GUARD_RETURN(ACE_Thread_Mutex, guard, lock_, -1);
        --queued_count_;
        if (queued_count_ == 0)
            close_now = deferred_close_;
    }

    if (close_now)
        return Logging_Event_Handler::handle_close(handle, mask);

    return 0;
}


// vim: set et ts=4 sts=4 sw=4:
