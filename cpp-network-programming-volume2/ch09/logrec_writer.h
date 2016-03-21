/// \file logrec_writer.h
/// \brief The Logrec_Writer class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-20

#ifndef LOGREC_WRITER_H
#define LOGREC_WRITER_H

#include "logrec_module.h"
#include <ace/Task.h>

class Logrec_Writer: public ACE_Task<ACE_MT_SYNCH>
{
public:
    virtual int open(void*);
    virtual int put(ACE_Message_Block *mblk, ACE_Time_Value *to);
    virtual int svc();
};

LOGREC_MODULE(Logrec_Writer);

#endif /* !LOGREC_WRITER_H */
// vim: set et ts=4 sts=4 sw=4:

