/// \file cld_handler.h
/// \brief The Cld_Handler class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-13

#ifndef CLD_HANDLER_H
#define CLD_HANDLER_H

#include "cld_export.h"
#include "cld_connector.h"
#include <ace/Event_Handler.h>
#include <ace/Message_Queue.h>
#include <ace/Thread_Manager.h>
#include <ace/Log_Record.h>
#include <ace/SOCK_Stream.h>

#if !defined(FLUSH_TIMEOUT)
#   define FLUSH_TIMEOUT 120
#endif /* !FLUSH_TIMEOUT */

class CLD_Handler: public ACE_Event_Handler
{
public:
    enum { QUEUE_MAX = sizeof(ACE_Log_Record) * ACE_IOV_MAX };

    /// \brief Initialization hook method.
    virtual int open(CLD_Connector*);
    /// \brief Shutdown hook method.
    virtual int close();

    /// \brief Accessor to the connection to the logging server.
    virtual ACE_SOCK_Stream &peer() {
        return peer_;
    }

    /// \brief Reactor hook methods.
    virtual int handle_input(ACE_HANDLE handle);
    virtual int handle_close(ACE_HANDLE = ACE_INVALID_HANDLE,
                             ACE_Reactor_Mask = 0);

protected:
    /// \brief Forward log records to the server logging daemon.
    virtual ACE_THR_FUNC_RETURN forward();

    /// \brief Send buffered log records using a gather-write operation.
    virtual int send(ACE_Message_Block *chunk[], size_t &count);

    /// \brief Entry point into forwarder thread of control.
    static ACE_THR_FUNC_RETURN run_svc(void *arg);

    /// \brief A synchronized <ACE_Message_Queue> that queue messages.
    ACE_Message_Queue<ACE_MT_SYNCH> msg_queue_;

    /// \brief Manage the forwarder thread.
    ACE_Thread_Manager thr_mgr_;

    /// \brief Pointer to our <CLD_Connector>.
    CLD_Connector *connector_;

    /// \brief Connection to the logging server.
    ACE_SOCK_Stream peer_;
};

#endif /* !CLD_HANDLER_H */
// vim: set et ts=4 sts=4 sw=4:
