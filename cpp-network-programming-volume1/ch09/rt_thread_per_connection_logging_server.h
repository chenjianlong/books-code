/// \file rt_thread_per_connection_logging_server.h
/// \brief The RT_Thread_Per_Connection_Logging_Server class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-03

#ifndef RT_THREAD_PER_CONNECTION_LOGGING_SERVER_H
#define RT_THREAD_PER_CONNECTION_LOGGING_SERVER_H

#include "thread_per_connection_logging_server.h"

class RT_Thread_Per_Connection_Logging_Server:
    public Thread_Per_Connection_Logging_Server
{
public:
    virtual int open(u_short port);

protected:
    virtual int handle_data(ACE_SOCK_Stream *logging_client);
};

#endif /* !RT_THREAD_PER_CONNECTION_LOGGING_SERVER_H */
// vim: set et ts=4 sts=4 sw=4:
