/// \file tss_thread_per_connection_logging_server.h
/// \brief The TSS_Thread_Per_Connection_Logging_Server class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-03

#ifndef TSS_THREAD_PER_CONNECTION_LOGGING_SERVER_H
#define TSS_THREAD_PER_CONNECTION_LOGGING_SERVER_H

#include "thread_per_connection_logging_server.h"

class TSS_Thread_Per_Connection_Logging_Server:
    public Thread_Per_Connection_Logging_Server
{
protected:
    virtual int handle_data(ACE_SOCK_Stream *);
};

#endif /* !TSS_THREAD_PER_CONNECTION_LOGGING_SERVER_H */
// vim: set et ts=4 sts=4 sw=4:
