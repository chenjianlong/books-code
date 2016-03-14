/// \file tp_logging_task.h
/// \brief The Tp_Logging_Task class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-14

#ifndef TP_LOGGING_TASK_H
#define TP_LOGGING_TASK_H

#include <ace/Task.h>
#include <ace/Singleton.h>

class TP_Logging_Task: public ACE_Task<ACE_MT_SYNCH>
{
public:
    enum { MAX_THREADS = 4 };

    virtual int open(void* = 0);
    virtual int put(ACE_Message_Block *mblk, ACE_Time_Value *timeout = 0);

protected:
    int svc();
};

typedef ACE_Unmanaged_Singleton<
    TP_Logging_Task, ACE_Null_Mutex> TP_LOGGING_TASK;

#endif /* !TP_LOGGING_TASK_H */
// vim: set et ts=4 sts=4 sw=4:
