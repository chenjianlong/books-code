#include "logrec_reader.h"
#include <ace/FILE_Addr.h>
#include <ace/FILE_Connector.h>
#include <ace/CDR_Stream.h>
#include <ace/OS_NS_string.h>
#include <iostream>

using namespace std;

int Logrec_Reader::open(void*)
{
    cerr << "Logrec_Reader::open" << endl;
    ACE_FILE_Addr name(filename_.c_str());
    ACE_FILE_Connector con;
    if (con.connect(logfile_, name) == -1)
        return -1;

    return activate();
}

int Logrec_Reader::svc()
{
    cerr << "Logrec_Reader::svc" << endl;
    const size_t FILE_READ_SIZE = 8 * 1024;
    ACE_Message_Block mblk(FILE_READ_SIZE);

    for (;; mblk.crunch()) {
        ssize_t bytes_read = logfile_.recv(mblk.wr_ptr(), mblk.space());
        if (bytes_read <= 0) {
            cerr << "Logrec_Reader::svc bytes_read <= 0" << endl;
            break;
        }

        cerr << "Logrec_Reader::svc bytes_read " << bytes_read << endl;
        mblk.wr_ptr(static_cast<size_t>(bytes_read));
        for (;;) {
            size_t name_len = ACE_OS::strnlen(mblk.rd_ptr(), mblk.length());
            if (name_len == mblk.length())
                break;

            char *name_p = mblk.rd_ptr();
            cerr << "name=" << name_p << endl;
            ACE_Message_Block *rec = 0, *head = 0, *temp = 0;
            ACE_NEW_RETURN(head, ACE_Message_Block(name_len, MB_CLIENT), 0);
            head->copy(name_p, name_len);
            mblk.rd_ptr(name_len + 1);

            size_t need = mblk.length() + ACE_CDR::MAX_ALIGNMENT;
            ACE_NEW_RETURN(rec, ACE_Message_Block(need), 0);
            ACE_CDR::mb_align(rec);
            rec->copy(mblk.rd_ptr(), mblk.length());

            ACE_InputCDR cdr(rec);
            rec->release();
            ACE_CDR::Boolean byte_order;
            if (!cdr.read_boolean(byte_order)) {
                head->release();
                mblk.rd_ptr(name_p);
                break;
            }
            cdr.reset_byte_order(byte_order);

            ACE_CDR::ULong length;
            if (!cdr.read_ulong(length)) {
                head->release();
                mblk.rd_ptr(name_p);
                break;
            }

            if (length > cdr.length()) {
                head->release();
                mblk.rd_ptr(name_p);
                break;
            }

            ACE_NEW_RETURN(temp, ACE_Message_Block(length, MB_TEXT), 0);
            ACE_NEW_RETURN(temp, ACE_Message_Block(2 * sizeof(ACE_CDR::Long), MB_TIME, temp), 0);
            ACE_NEW_RETURN(temp, ACE_Message_Block(sizeof(ACE_CDR::Long), MB_PID, temp), 0);
            ACE_NEW_RETURN(temp, ACE_Message_Block(sizeof(ACE_CDR::Long), MB_TYPE, temp), 0);
            head->cont(temp);
            // Extract the type
            ACE_CDR::Long *lp = reinterpret_cast<ACE_CDR::Long*>(temp->wr_ptr());
            cdr >> *lp;
            temp->wr_ptr(sizeof(ACE_CDR::Long));
            temp = temp->cont();
            // Extract the PID
            lp = reinterpret_cast<ACE_CDR::Long*>(temp->wr_ptr()); 
            cdr >> *lp; 
            temp->wr_ptr(sizeof(ACE_CDR::Long)); 
            temp = temp->cont(); 
            // Extract the timestamp
            ACE_CDR::LongLong *llp = reinterpret_cast<ACE_CDR::LongLong*>(temp->wr_ptr());
            cdr >> *llp;
            lp = reinterpret_cast<ACE_CDR::Long*>(temp->wr_ptr() + sizeof(ACE_CDR::LongLong));
            cdr >> *lp;
            temp->wr_ptr(2 * sizeof(ACE_CDR::Long));
            temp = temp->cont();
            // Extract the text length, then the text message
            ACE_CDR::ULong text_len;
            cdr >> text_len;
            cerr << "text_len: " << text_len << endl;
            cdr.read_char_array(temp->wr_ptr(), text_len);
            temp->wr_ptr(text_len);
            if (put_next(head) == -1)
                break;

            mblk.rd_ptr(mblk.length() - cdr.length());
        }
    }

    ACE_Message_Block *stop = 0;
    ACE_NEW_RETURN(stop, ACE_Message_Block(0, ACE_Message_Block::MB_STOP), 0);
    put_next(stop);
    cerr << "Logrec_Reader::svc end" << endl;
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
