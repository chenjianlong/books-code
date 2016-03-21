/// \file logrec_separator.h
/// \brief The Logrec_Separator class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-20

#ifndef LOGREC_SEPARATOR_H
#define LOGREC_SEPARATOR_H

#include "logrec_module.h"
#include <ace/Task.h>
#include <ace/Lock_Adapter_T.h>

class Logrec_Separator: public ACE_Task<ACE_MT_SYNCH>
{
public:
    virtual int put(ACE_Message_Block *mblk, ACE_Time_Value*);

private:
    ACE_Lock_Adapter<ACE_Thread_Mutex> lock_strategy_;
};

LOGREC_MODULE(Logrec_Separator);
#endif /* !LOGREC_SEPARATOR_H */
// vim: set et ts=4 sts=4 sw=4:
