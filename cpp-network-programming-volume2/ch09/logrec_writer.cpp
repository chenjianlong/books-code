#include "logrec_writer.h"
#include <ace/ACE.h>
#include <iostream>

using namespace std;

int Logrec_Writer::open(void*)
{
    cerr << "Logrec_Writer::open" << endl;
    return activate();
}

int Logrec_Writer::put(ACE_Message_Block *mblk, ACE_Time_Value *to)
{
    return putq(mblk, to);
}

int Logrec_Writer::svc()
{
    cerr << "Logrec_Writer::svc" << endl;
    int stop = 0;
    for (ACE_Message_Block *mb; !stop && getq(mb) != -1;) {
        cerr << "Logrec_Writer process mb" << endl;
        if (mb->msg_type() == ACE_Message_Block::MB_STOP) {
            stop = 1;
        } else {
            cerr << "write_n" << endl;
            ACE::write_n(ACE_STDOUT, mb);
        }

        put_next(mb);
    }

    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
