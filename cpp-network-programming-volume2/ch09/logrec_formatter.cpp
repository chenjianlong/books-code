#include "logrec_formatter.h"
#include "logrec_reader.h"
#include <ace/CDR_Stream.h>
#include <iostream>

using namespace std;

static void format_client(ACE_Message_Block*)
{
    return;
}

static void format_long(ACE_Message_Block *mblk)
{
    ACE_CDR::Long type = * (ACE_CDR::Long*) mblk->rd_ptr();
    mblk->size(11); // Max size in ASCII of 32-bit word.
    mblk->reset();
    mblk->wr_ptr((size_t) sprintf(mblk->wr_ptr(), "%d", type));
}

static void format_time(ACE_Message_Block *mblk)
{
    ACE_CDR::LongLong secs = * (ACE_CDR::LongLong*) mblk->rd_ptr();
    mblk->rd_ptr(sizeof(ACE_CDR::LongLong));
    ACE_CDR::Long usecs = * (ACE_CDR::Long*) mblk->rd_ptr();
    char timestamp[26]; // Max size of ctime_r() string.
    time_t time_secs(secs);
    ACE_OS::ctime_r(&time_secs, timestamp, sizeof(timestamp));
    mblk->size(26);
    mblk->reset();
    timestamp[19] = '\0'; // NUL-terminate after the time.
    timestamp[24] = '\0'; // NUL-terminate after the date.
    size_t fmt_len = (sprintf(
        mblk->wr_ptr(),
        "%s.%03d %s", timestamp + 4, usecs / 1000, timestamp + 20));
    mblk->wr_ptr(fmt_len);
}

static void format_string(ACE_Message_Block *mblk)
{
    ACE_UNUSED_ARG(mblk);
    cerr << "format_string" << endl;
    return;
}

Logrec_Formatter::FORMATTER Logrec_Formatter::format_ = {
    format_client, format_long, format_long, format_time, format_string
};

int Logrec_Formatter::put(ACE_Message_Block *mblk, ACE_Time_Value*)
{
    cerr << "Logrec_Formatter::put" << endl;
    if (mblk->msg_type() == Logrec_Reader::MB_CLIENT) {
        for (ACE_Message_Block *temp = mblk; temp != 0; temp = temp->cont()) {
            int mb_type = temp->msg_type() - ACE_Message_Block::MB_USER;
            (*format_[mb_type])(temp);
        }
    }

    return put_next(mblk);
}


// vim: set et ts=4 sts=4 sw=4:
