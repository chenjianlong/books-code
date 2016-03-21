/// \file logrec_formatter.h
/// \brief The Logrec_Formatter class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-20

#ifndef LOGREC_FORMATTER_H
#define LOGREC_FORMATTER_H

#include "logrec_module.h"
#include <ace/Task.h>

class Logrec_Formatter: public ACE_Task<ACE_MT_SYNCH>
{
public:
    virtual int put(ACE_Message_Block *mblk, ACE_Time_Value*);

private:
    typedef void (*FORMATTER[5])(ACE_Message_Block*);
    static FORMATTER format_;
};

LOGREC_MODULE(Logrec_Formatter);

#endif /* !LOGREC_FORMATTER_H */
// vim: set et ts=4 sts=4 sw=4:
