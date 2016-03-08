/// \file logging_event_handler_wfmo.h
/// \brief The Logging_Event_Handler_WFMO class implementation.
/// \author Jianlong Chen <jianlong99@gmail.com>
/// \date 2016-03-08

#ifndef LOGGING_EVENT_HANDLER_WFMO_H
#define LOGGING_EVENT_HANDLER_WFMO_H

#include "logging_event_handler_ex.h"

class Logging_Event_Handler_WFMO: public Logging_Event_Handler_Ex
{
public:
    Logging_Event_Handler_WFMO(ACE_Reactor *r): Logging_Event_Handler_Ex(r) {
    }

protected:
    virtual int handle_input(ACE_HANDLE h) {
        ACE_GUARD_RETURN(ACE_SYNCH_MUTEX, monitor, lock_, -1);
        return logging_handler_.log_record();
    }

    ACE_Thread_Mutex lock_;
};

#endif /* !LOGGING_EVENT_HANDLER_WFMO_H */
// vim: set et ts=4 sts=4 sw=4:
