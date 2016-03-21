#include "logrec_separator.h"
#include "logrec_reader.h"
#include <iostream>

using namespace std;

int Logrec_Separator::put(ACE_Message_Block *mblk, ACE_Time_Value*)
{
    cerr << "Logrec_Separator::put" << endl;
    if (mblk->msg_type() == Logrec_Reader::MB_CLIENT) {
        ACE_Message_Block *separator = 0;
        ACE_NEW_RETURN(separator,
                ACE_Message_Block(
                    ACE_OS::strlen("|") + 1, ACE_Message_Block::MB_DATA,
                    0, 0, 0, &lock_strategy_), -1);
        separator->copy("|");

        ACE_Message_Block *dup = 0;
        for (ACE_Message_Block *temp = mblk; temp != 0;) {
            dup = separator->duplicate();
            dup->cont(temp->cont());
            temp->cont(dup);
            temp = dup->cont();
        }

        ACE_Message_Block *nl = 0;
        ACE_NEW_RETURN(nl, ACE_Message_Block(2), 0);
        nl->copy("\n");
        dup->cont(nl);
        separator->release();
    }

    return put_next(mblk);
}
// vim: set et ts=4 sts=4 sw=4:
