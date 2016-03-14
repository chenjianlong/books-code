/// \file tp_logging_handler.h
/// \brief The Tp_Logging_Handler class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-14

#ifndef TP_LOGGING_HANDLER_H
#define TP_LOGGING_HANDLER_H

#include "logging_event_handler.h"

class TP_Logging_Handler: public Logging_Event_Handler
{
public:
    friend class TP_Logging_Acceptor;

    TP_Logging_Handler(ACE_Reactor *reactor):
        Logging_Event_Handler(reactor), queued_count_(0), deferred_close_(0) {
    }

    virtual int handle_input(ACE_HANDLE);
    virtual int handle_close(ACE_HANDLE, ACE_Reactor_Mask);

protected:
    virtual ~TP_Logging_Handler() {
    }

    /// \brief Number of pointers to this class instance that currently reside
    //         in the <TP_LOGGING_TASK> singleton's message queue.
    int queued_count_;

    /// \brief Indicates whether <Logging_Event_Handler::handle_close()>
    ///        must be called to cleanup and delete this object.
    int deferred_close_;

    /// \brief Serialize access to <queued_count_> and <deferred_close_>.
    ACE_Thread_Mutex lock_;
};

#endif /* !TP_LOGGING_HANDLER_H */
// vim: set et ts=4 sts=4 sw=4:
