#include <ace/ACE.h>
#include <ace/Message_Block.h>

int main(int, char *[])
{
    ACE_Message_Block *head = new ACE_Message_Block(BUFSIZ);
    ACE_Message_Block *mblk = head;

    for (size_t recvd = 0; true; recvd = 0) {
        ssize_t nbytes = ACE::read_n(
            ACE_STDIN, mblk->wr_ptr(), mblk->size(), &recvd);
        mblk->wr_ptr(recvd);
        if (nbytes <= 0)
            break;

        mblk->cont(new ACE_Message_Block(BUFSIZ));
        mblk = mblk->cont();
    }

    for (mblk = head; mblk != 0; mblk = mblk->cont()) {
        ACE::write_n(ACE_STDOUT, mblk->rd_ptr(), mblk->length());
    }

    head->release();
    return 0;
}
// vim: set et ts=4 sts=4 sw=4:
